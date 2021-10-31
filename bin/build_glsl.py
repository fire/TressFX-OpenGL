import re
import sys
import subprocess
from os import path

SHADERS_DIR = 'src/shaders'
SHADERS_OUT_DIR = 'src/shaders/generated'

SHADER_FILES = [
    'gl-tfx/ppll_build.vert.glsl',
    'gl-tfx/ppll_build.frag.glsl',
    'gl-tfx/ppll_resolve.vert.glsl',
    'gl-tfx/ppll_resolve.frag.glsl',
    'gl-tfx/sim0_IntegrationAndGlobalShapeConstraints.comp.glsl',
    'gl-tfx/sim1_VelocityShockPropagation.comp.glsl',
    'gl-tfx/sim2_LocalShapeConstraints.comp.glsl',
    'gl-tfx/sim3_LengthConstraintsWindAndCollision.comp.glsl',
    'gl-tfx/sim4_UpdateFollowHairVertices.comp.glsl'
]

INCLUDE_REGEX = '^#pragma include "(.*?)"'
NVIDIA_ERR_REGEX = '^.*\((.*?)\).:.(.*?) .+?: (.*)$'


class Colors:
    BLACK   = '\033[0;{}m'.format(30)
    RED     = '\033[0;{}m'.format(31)
    GREEN   = '\033[0;{}m'.format(32)
    YELLOW  = '\033[0;{}m'.format(33)
    BLUE    = '\033[0;{}m'.format(34)
    MAGENTA = '\033[0;{}m'.format(35)
    CYAN    = '\033[0;{}m'.format(36)
    WHITE   = '\033[0;{}m'.format(37)

def process_file(filepath):
  buf = []
  with open(filepath) as f:
    lines = f.readlines()
    for line in lines:
      included_file = re.search(INCLUDE_REGEX, line, re.IGNORECASE)
      if included_file:
        file_to_include = path.join(path.dirname(filepath), included_file.group(1))
        print('  include: ', file_to_include)
        buf.extend(process_file(file_to_include))
      else:
        buf.append(line)
  return buf

def process_error_line(err_line, shader_lines):
    matches = re.search(NVIDIA_ERR_REGEX, err_line, re.IGNORECASE)
    if matches:
        line_no, level, msg = int(matches.group(1)), matches.group(2), matches.group(3)
        line = shader_lines[line_no - 1].strip()
        is_warn = level == 'warning'
        col = Colors.YELLOW if is_warn else Colors.RED
        level_str = 'Warn' if is_warn else 'Err'

        print('{}[L{}] {}: {}'.format(col, line_no, level_str, msg))
        print('{}   > {}{}'.format(Colors.CYAN, line, Colors.WHITE))
    else:
        print(err_line)

if __name__ == '__main__':
    has_error = False
    for filepath in SHADER_FILES:
        in_path = path.join(SHADERS_DIR, filepath)
        out_path = path.join(SHADERS_OUT_DIR, filepath)
        print(in_path, ' => ', out_path)

        after_processing = process_file(in_path)
        new_file_content = ''.join(after_processing)

        with open(out_path, 'w') as f:
            f.write(new_file_content)

    if has_error:
        sys.exit(1)
    print()
