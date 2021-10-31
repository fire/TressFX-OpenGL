#pragma once

#define GL_UTILS_NOT_CREATED_ID 0xffffffff

#define GFX_FAIL(...) \
  { \
    LOGE << "Assert failed (" << __FILE__ << ":" << __LINE__ << ") " APPLY(<<, __VA_ARGS__); \
		 \
    assert(false); \
  }

#define GFX_FAIL_IF(condition, ...) \
  if ((condition)) { \
     GFX_FAIL("Failed condition '" , #condition , "' " , __VA_ARGS__) \
	}

#define GFX_FAIL_IF_NULL(PTR) \
		if ((PTR) == nullptr) { \
			GFX_FAIL("Expected pointer '" , #PTR , "' to not be null") \
		}

#  define GFX_GL_CALL(fn, ...) fn(__VA_ARGS__)