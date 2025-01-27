# TressFX OpenGL

Direct port of AMD's TressFX hair/fur rendering and simulation technology to OpenGL.

*Unfortunately, Sintel is not the most remarkable example to demonstrate TressFX on. Read more in the FAQ part of this readme!*

https://user-images.githubusercontent.com/32321/139611908-f75b0092-8b48-4515-8965-a83bc4cf36e3.mp4

## What is this?

[TressFX](//en.wikipedia.org/wiki/TressFX) is AMD's library used for simulation and rendering of hair. It has been used in commercial games like the newest Tomb Raider titles and Deus Ex: Mankind Divided. The library itself is [open source](//github.com/GPUOpen-Effects/TressFX) under the GPUOpen initiative. Please visit provided links to get more details.

AMD's version of TressFX uses HLSL (DirectX's shading language) and the Sushi framework. It also provides a fill-the-gaps library that is independent of the rest of the source code ([includes](https://github.com/GPUOpen-Effects/TressFX/tree/master/amd_tressfx/inc), [source](https://github.com/GPUOpen-Effects/TressFX/tree/master/amd_tressfx/src)). The main focus of my project was to provide the implementation for various methods needed to render and simulate hair using OpenGL and GLSL. I tried to stick to AMD's version as closely as possible, even if it would have been easier to write everything from grounds up.

## Usage

Use the releases or see the Github workflows.

## FAQ

**Q: What is unimplemented?**

A: Due to time constraints following techniques are not yet implemented:

* Shortcut for Order Independent Transparency (older Per-Pixel Linked List used instead)
* Skinning (I am not sure how to get this information from Blender)
* Signed Distance Field-based collisions (older collision capsules are used instead)
* Shadows
* Realistic rendering (looks like spaghetti right now, though it is considerably better when viewed in motion on full resolution instead of tiny gif), incl. proper Anti-Aliasing
* Global Shape Constraints from blender-imported models (works fine with AMD's samples). I guess I would have to go deeper into how they generate some data for simulation. Currently, the Blender plugin is a **massive** hack. It could be anything from offsets to left/right-hand coordinate system mismatch.
* [Cyrill Crassin's PPLL OIT improvements](http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html)

**Q: Required OpenGL version?**

A: Use 4.5+. Technically direct state access(DSA), shader storage buffer object(SSBO), compute shaders, image load/store, atomic ops are required. They could be used through extensions, but You would probably have to write support for them by hand. So use 4.5+, and it should work.

**Q: Some warnings during compilation?**

A: They are from AMD's code that is included. AMD had used the visual studio, so there were a few things I had to change to make it compile under clang. See next question.

**Q: What changes were needed compared to AMD's library?**

A: [Complete list](libs/amd_tressfx/src/Readme.md). I tried to keep the changes to a minimum, even if it included having warnings during compilation. My API is also modelled to be as close as possible.

**Q: Is this a Blender plugin?**

A: [Sure](assets/sintel_lite_v2_1/tfx_exporter.py). It is a very bare-bones ATM, I will probably make a separate Github repo for it. It does not support .tfxbone (skinning) and per-strand UV, but it is enough for simulation and basic rendering. It should work with AMD's viewer, although I did not test it.

**Q: How to load new models?**

A: Authoring new models for TressFX is quite complicated. First, there is the scale. Second, there are certain simulation steps that require models to have roughly comparable scales. A good example is wind: displacing a hair strand with a length of 3 units is vastly different from a hair strand 300 units long. Sintel's model is about 50x50x50 blender units.

Another thing is tweaking all simulation and rendering parameters. E.g. AMD's library calculates random vectors around the guide hair where follow hair will be placed. Since You do not have any input in this (unless You modify AMD's library, which I tried not to do), it may be required to tweak it later.

There are also collision capsules that are hard to get right. When hair near the root intersects with the collision capsule, it is automatically 'pushed away.' Collision resolve has the highest priority, resulting in colliding part of the hair strand just ignoring any other simulation forces. One could make the capsules smaller, but that leads to penetration of the object.

Fortunately, just getting it to display requires only importing the model from Blender / Maya.

**Q: Available models?**

A: Found in [assets](assets):

* Sintel from Blender institute
* Ratboy's Mohawk from original AMD TressFX

**Q: Sintel? How cool!**

A: Well, I made a rule to **not modify the original Sintel lite hair model**. Absolutely no content authoring, even minor fixes. As a result, a few issues can probably be noticed when watching the animations above. The biggest issue is the wind that blows from one side and pushes half of the hair strands 'into' the head model. This is resolved as a collision with the collision capsule and fixed by the overriding strand position. Which in turn results in half of the hair just ignoring wind altogether. I think one could solve this by using multiple wind sources instead of averaging? Alternatively, properly author the model.

We can compare this to models from commercial games that utilize TressFX:

* Adam Jensen (Deus Ex: Mankind Divided) has short hair.
* Lara Croft's (Tomb Raider 2013, Rise of the Tomb Raider) ponytail acts more like a ribbon with considerably simpler interactions with the rest of the model (though I assume it still was a nightmare to get the parameters right). The rest of the hairstyle is somewhat stiff in comparison. This is in stark contrast to Sintel, where whole hair is purely under the control of the simulation.
  PS. Rise of The Tomb Raider used the evolution of TressFX 3.0 called [PureHair](https://www.youtube.com/watch?v=wrhSVcZF-1I). In the video, You can see what an experienced artist can do with a system like TressFX. Interestingly, not all hair is simulated, but only a few strands in key places (like bangs). However, it still gives a dynamic feeling.

**Q: What is glUtils?**

A: **VERY** thin wrapper around OpenGL. Thin as in 'You still have to write most of gl- calls anyway' thin. It mostly deals with resource creation. It was made to make OpenGL API more functional. Good example is [glUtils::apply_draw_parameters](src/gl-utils/draw/apply_parameters.impl.hpp) that takes [DrawParameters](include/gl-utils/draw/parameters.hpp) structure as an argument. Feel free to look around, and there are some comments about how does OpenGL works out there that You may find interesting.

**Q: What to do if I have a problem?**

A: In [main()](src/main.cpp) set log level to trace: `logger:: Log:: ReportingLevel = logger:: Trace; ` . It will generate A LOT of text into the console. Also, the code is CRAMMED with assertions. And if the assertion is not clear enough, go to the code line (printed with assertion message). There is usually a comment about what could have gone wrong.

## Other videos

https://user-images.githubusercontent.com/32321/139611899-2451c8ec-fc88-40f7-891d-ebaaeb727484.mp4

## Honorable mentions and other third party stuff

* AMD for TressFX
* [GLM](https://glm.g-truc.net/0.9.9/index.html)
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [GLAD](https://github.com/Dav1dde/glad)
* [imgui](https://github.com/ocornut/imgui) <3
* [tiny_obj_loader](https://github.com/syoyo/tinyobjloader)
* [apitrace](http://apitrace.github.io/)
* [RenderDoc](https://renderdoc.org/)
* [Blender](https://www.blender.org/), [Blender Institute](https://www.blender.org/institute/) <3
    Sintel's model under [CC 3.0](https://durian.blender.org/sharing/), the character was simplified into a bust. © copyright Blender Foundation | durian.blender.org

## Licencing

Certain parts of this project are under [AMD's licence](https://github.com/GPUOpen-Effects/TressFX/blob/master/LICENSE.txt) (which is MIT) - usually noted as a licence file in the directory or file header. Rest is under the licence of this project (which is also MIT).
