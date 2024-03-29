#ifndef INTERFACE
#define INTERFACE

#ifdef HI3531D
#define INTERFACE_VIDEO "HDMI-A";
#define INTERFACE_VIDEO2 "HDMI-B";
#define INTERFACE_AUDIO "HDMI-A";
#define INTERFACE_AUDIO2 "HDMI-B";
#elif defined HI3521D
#define INTERFACE_VIDEO "HDMI";
#define INTERFACE_VIDEO2 "HDMI";
#define INTERFACE_AUDIO "HDMI";
#define INTERFACE_AUDIO2 "HDMI";
#elif defined HI3519A
#define INTERFACE_VIDEO "HDMI-L";
#define INTERFACE_VIDEO2 "SDI";
#define INTERFACE_AUDIO "HDMI";
#define INTERFACE_AUDIO2 "SDI";
#elif defined HI3531DV200
#define INTERFACE_VIDEO "HDMI-A";
#define INTERFACE_VIDEO2 "HDMI-B";
#define INTERFACE_AUDIO "HDMI-A";
#define INTERFACE_AUDIO2 "HDMI-B";
#endif

#endif // INTERFACE

