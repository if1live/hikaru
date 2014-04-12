// Ŭnicode please
#pragma once

//platform check macro
#if __APPLE__
//iphone check
//#import <Availability.h>
//#if __IPHONE_2_0
#define _IPHONE_ 1
//#endif
#else
#define _IPHONE_ 0
#endif

#if (defined _WIN32) || (defined _W64)
#define _WIN_ 1
#else
#define _WIN_ 0
#endif

//android check
#if (_IPHONE_ == 0) && (_WIN_ == 0)
	#define _ANDROID_ 1
#else
	#define _ANDROID_ 0
#endif

//pch
#if _WIN_ || _IPHONE_
#define _PCH_ 1
#else
#define _PCH_ 0
#endif