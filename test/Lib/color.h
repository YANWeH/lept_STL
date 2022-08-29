/*************************************************************************
	> File Name: color.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 28 Jul 2022 05:02:45 AM EDT
 ************************************************************************/

#ifndef LEPT_FINALRES_IO_COLOR_H__ 
#define LEPT_FINALRES_IO_COLOR_H__ 

#include <unistd.h>     /* getenv() */
#include <cstring>      /* strstr() */
#include <cstdlib>
#include <iostream>
#include <type_traits>  /* is_same enable_if ;可实现在编译时期计算、判断、转换、查询type的功能 */

namespace finalres
{
    namespace io 
    {
        enum class format 
        {
            reset       = 0,        /* all attributes off */
            bold        = 1,        /* 粗体或增粗 */
            faint       = 2,        /* 变细 */
            italic      = 3,        /* 斜体 */
            underline   = 4,        /* 下划线 */
            blinkslow   = 5,        /* blink slowly */
            blinkrapid  = 6,        /* blink fastly */
            inverse     = 7,        /* swap foreground and background */
            conceal     = 8,        /* 隐藏文本 */
            strikeline  = 9         /* 文字清晰，但有删除标记 */
        };
        /* set the foreground color */
        enum class fg 
        {
            black   = 30,
            red     = 31,
            green   = 32,
            yellow  = 33,
            blue    = 34,
            purple  = 35,
            cyan    = 36,
            white   = 37,
            reserve = 38,
            reset   = 39
        };
        /* set the background color */
        enum class bg 
        {
            black   = 40,
            red     = 41,
            green   = 42,
            yellow  = 43,
            blue    = 44,
            purple  = 45,
            cyan    = 46,
            white   = 47,
            reserve = 38,
            reset   = 39

        };
        /* set the highlight foreground color */
        enum class hfg 
        {
            black   = 90,
            red     = 91,
            green   = 92,
            yellow  = 93,
            blue    = 94,
            purple  = 95,
            cyan    = 96,
            white   = 97
        };
        /* set the highlight backgound color */
        enum class hbg 
        {
            black   = 100,
            red     = 101,
            green   = 102,
            yellow  = 103,
            blue    = 104,
            purple  = 105,
            cyan    = 106,
            white   = 107
        };
        /* set the control state */
        enum class state 
        {
            automatic   = 0,
            manual      = 1
        };

        /************************************************************/
        /* details */
        namespace details
        {
            /* manages associated stream buffer */
            inline const std::streambuf*& get_coutbuf()
            {
                static const std::streambuf* pout = std::cout.rdbuf();
                return pout;
            }
            inline const std::streambuf*& get_cerrbuf()
            {
                static const std::streambuf* perr = std::cerr.rdbuf();
                return perr;
            }
            inline const std::streambuf*& get_clogbuf()
            {
                static const std::streambuf* plog = std::clog.rdbuf();
                return plog;
            }

            /* get an unique integer to use as index to iword() */
            inline int get_iword()
            {
                static int i = std::ios_base::xalloc();
                return i;
            }
            /* determines whether the terminal color of this system can be modified */
            inline bool is_modifiable()
            {
                static constexpr const char* terms[] = {
                    "ansi", "color", "console", "cygwin", "gnome", "knosole", "kterm",
                    "linux", "msys", "putty", "rxvt", "screen", "vt100", "xterm"
                };
                const char* penv = std::getenv("TERM");
                if(penv == nullptr)
                    return false;
                bool result = false;
                for(const auto& t:terms)
                {
                    if(std::strstr(penv, t) != nullptr)
                    {
                        result = true;
                        break;
                    }
                }
                return result;
            }
            /* determines whether the buffer stream reached the end */
            inline bool is_terminal(const std::streambuf* buf)
            {
                if(buf == get_coutbuf())
                    return isatty(fileno(stdout))?true:false;
                if(buf == get_cerrbuf() || buf == get_clogbuf())
                    return isatty(fileno(stderr))?true:false;
                return false;
            }

            /* for overloading standard output stream */
            template <typename T>
                using color_return_t = typename std::enable_if<
                std::is_same<T, finalres::io::format>::value ||
                std::is_same<T, finalres::io::fg>::value ||
                std::is_same<T, finalres::io::bg>::value ||
                std::is_same<T, finalres::io::hfg>::value ||
                std::is_same<T, finalres::io::hbg>::value,
                std::ostream&>::type;

            template <typename T>
                using state_return_t = typename std::enable_if<
                std::is_same<T, finalres::io::state>::value,
                std::ostream&>::type;

            /* set the format and color of the text */
            template <typename T>
                inline color_return_t<T> set_color(std::ostream& os, const T& value)
                {
                    return os  << "\033[" << static_cast<int>(value) << "m";
                }
        }   /* namespace details */

        /*****************************************************/
        /* overloads standard output stream to control the color of text */
        template <typename T>
            inline details::color_return_t<T>
            operator<<(std::ostream& os, const T& value)
            {
                return (os.iword(details::get_iword()) ||
                        (details::is_modifiable() &&
                         details::is_terminal(os.rdbuf())))
                    ? details::set_color(os, value)
                    : os;
            }
        template <typename T>
            inline details::state_return_t<T>
            operator<<(std::ostream& os, const T& value)
            {
                if(value == finalres::io::state::automatic)
                    os.iword(details::get_iword()) = 0;
                else if(value == finalres::io::state::manual)
                    os.iword(details::get_iword()) = 1;
                return os;
            }
    }   /* namespace io */
}       /* namespace finalres */
#endif /* LEPT_FINALRES_IO_COLOR_H__ */
