// VT INTERCO
// Copyright (c) 2024 James Holderness
// Distributed under the MIT License

#include "vt.h"

#include <array>

namespace {

    constexpr auto small_letters = std::to_array({
        R"("10;1#5!30~$"2;1#1!30?!25~^NFB@-!30?!19~^NFB@-!30?!16~r`-!30?!19~}{wo_-!30?!25~}{wo_)",
        R"("2;1#2!55~^NFB@-!49~^NFB@-!46~r`-!49~}{wo_-!55~}{wo_)",
        R"("12;1#1!60P$#5!60I$#2!60C)",
        R"("12;1#6!60P$#1!60M)",
        R"("10;1#1!60F$#2!60w)",
        R"("10;1#5!60~$"1;1#2!24?_ow{}~~}{wo_-!18?_ow{}!14~}{wo_-!12?_ow{}!26~}{wo_-!6?_ow{}!38~}{wo_-_ow{}!50~}{wo_-@BFN^!50~^NFB@-!6?@BFN^!38~^NFB@-!12?@BFN^!26~^NFB@-!18?@BFN^!14~^NFB@-!24?@BFN^~~^NFB@)",
        R"("10;1#1!60~$#6!10~!10?!10~!10?!10~)",
        R"("10;1#5!30~#2!30~)",
        R"("10;1#6!60~#8"1;1---!20?_ow{}}!8~}}{wo_-!18?_}!20~}_-!18?@^!20~^@-!20?@BFN^^!8~^^NFB@-)",
        R"("10;1#1!60r$#5!60K)",
        R"("10;1#6!30~#1!30~)",
        R"("10;1#8!60~$#6!30F!30w)",
        R"("10;1#1!60~$"1;1#5!6~}{wo_!38?_ow{}!6~-@BFN^!7~}{wo_!26?_ow{}!7~^NFB@-!6?@BFN^!7~}{wo_!14?_ow{}!7~^NFB@-!12?@BFN^!7~}{wo_??_ow{}!7~^NFB@-!18?@BFN^!14~^NFB@-!18?_ow{}!14~}{wo_-!12?_ow{}!7~^NFB@??@BFN^!7~}{wo_-!6?_ow{}!7~^NFB@!14?@BFN^!7~}{wo_-_ow{}!7~^NFB@!26?@BFN^!7~}{wo_-!6~^NFB@!38?@BFN^!6~)",
        R"("10;1#5!60~$"5;1#1!15F!15w!15F!15w-!15F!15w!15F!15w)",
        R"("10;1#2!60~$"1;1#6~}{wo_-!7~}{wo_-!13~}{wo_-!19~}{wo_-!25~}{wo_-!31~}{wo_-!37~}{wo_-!43~}{wo_-!49~}{wo_-!55~}{wo_)",
        R"("10;1#1!60~$#5!20?!20K)",
        R"("10;1#6!60~)",
        R"("12;1#2!60Z$#6!24C!12^!24C)",
        R"("10;1#5!60~$#1!20?!20K)",
        R"("10;1#2!20~#5!20~#1!20~)",
        R"("10;1#5!60~$#2!30F!30w)",
        R"("10;1#5!60~$"1;1#2!6~}{wo_!38?_ow{}!6~-@BFN^!7~}{wo_!26?_ow{}!7~^NFB@-!6?@BFN^!7~}{wo_!14?_ow{}!7~^NFB@-!12?@BFN^!7~}{wo_??_ow{}!7~^NFB@-!18?@BFN^!14~^NFB@-!18?_ow{}!14~}{wo_-!12?_ow{}!7~^NFB@??@BFN^!7~}{wo_-!6?_ow{}!7~^NFB@!14?@BFN^!7~}{wo_-_ow{}!7~^NFB@!26?@BFN^!7~}{wo_-!6~^NFB@!38?@BFN^!6~)",
        R"("10;1#1!60~$#5!10?!40]$#2!20?!20K)",
        R"("12;1#5!60Z$#1!24C!12^!24C)",
        R"("10;1#2!60~$"1;1#6!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@-~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@-!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}-?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!6~-!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@-~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@-!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}-?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!6~-!7~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@-~^NFB@!7?_ow{}!7~^NFB@!7?_ow{}!7~^NFB@)",
        R"("10;1#8!30~#1!30~$"1;1#6@BFN^!50~^NFB@-!6?@BFN^!38~^NFB@-!12?@BFN^!26~^NFB@-!18?@BFN^!14~^NFB@-!24?@BFN^~~^NFB@#2-!24?_ow{}}{wo_-!18?_ow{}!12~}{wo_-!12?_ow{}!24~}{wo_-!6?_ow{}!36~}{wo_-_ow{}!48~}{wo_)",
    });

    constexpr auto medium_letters = std::to_array({
        R"("20;1#5!60~$"2;1#1!60?!55~^NFB@-!60?!49~^NFB@-!60?!43~^NFB@-!60?!37~^NFB@-!60?!31~^NFB@-!60?!31~}{wo_-!60?!37~}{wo_-!60?!43~}{wo_-!60?!49~}{wo_-!60?!55~}{wo_)",
        R"("2;1#2!115~^NFB@-!109~^NFB@-!103~^NFB@-!97~^NFB@-!91~^NFB@-!91~}{wo_-!97~}{wo_-!103~}{wo_-!109~}{wo_-!115~}{wo_)",
        R"("24;1#1!120P$#5!120I$#2!120C)",
        R"("24;1#6!120P$#1!120M)",
        R"("20;1#1!120F$#2!120w)",
        R"("20;1#5!120~$"1;1#2!54?_ow{}~~}{wo_-!48?_ow{}!14~}{wo_-!42?_ow{}!26~}{wo_-!36?_ow{}!38~}{wo_-!30?_ow{}!50~}{wo_-!24?_ow{}!62~}{wo_-!18?_ow{}!74~}{wo_-!12?_ow{}!86~}{wo_-!6?_ow{}!98~}{wo_-_ow{}!110~}{wo_-@BFN^!110~^NFB@-!6?@BFN^!98~^NFB@-!12?@BFN^!86~^NFB@-!18?@BFN^!74~^NFB@-!24?@BFN^!62~^NFB@-!30?@BFN^!50~^NFB@-!36?@BFN^!38~^NFB@-!42?@BFN^!26~^NFB@-!48?@BFN^!14~^NFB@-!54?@BFN^~~^NFB@)",
        R"("20;1#1!120~$#6!20~!20?!20~!20?!20~)",
        R"("20;1#5!60~#2!60~)",
        R"("20;1#6!120~#8"6;1-"1;1!45?_oww{{}}}!12~}}}{{wwo_-!40?ow{}!32~}{wo-!37?_{!42~{_-!36?_!46~_-!36?@!46~@-!37?@N!42~N@-!40?BFN^!32~^NFB-!45?@BFFNN^^^!12~^^^NNFFB@-)",
        R"("20;1#1!120r$#5!120K)",
        R"("20;1#6!60~#1!60~)",
        R"("20;1#8!120~$#6!60F!60w)",
        R"("20;1#1!120~$"1;1#5!18~}{wo_!74?_ow{}!18~-!24~}{wo_!62?_ow{}!24~-!30~}{wo_!50?_ow{}!30~-@BFN^!31~}{wo_!38?_ow{}!31~^NFB@-!6?@BFN^!31~}{wo_!26?_ow{}!31~^NFB@-!12?@BFN^!31~}{wo_!14?_ow{}!31~^NFB@-!18?@BFN^!31~}{wo_??_ow{}!31~^NFB@-!24?@BFN^!62~^NFB@-!30?@BFN^!50~^NFB@-!36?@BFN^!38~^NFB@-!36?_ow{}!38~}{wo_-!30?_ow{}!50~}{wo_-!24?_ow{}!62~}{wo_-!18?_ow{}!31~^NFB@??@BFN^!31~}{wo_-!12?_ow{}!31~^NFB@!14?@BFN^!31~}{wo_-!6?_ow{}!31~^NFB@!26?@BFN^!31~}{wo_-_ow{}!31~^NFB@!38?@BFN^!31~}{wo_-!30~^NFB@!50?@BFN^!30~-!24~^NFB@!62?@BFN^!24~-!18~^NFB@!74?@BFN^!18~)",
        R"("20;1#5!120~$"10;1#1!30F!30w!30F!30w-!30F!30w!30F!30w)",
        R"("20;1#2!120~$"1;1#6~}{wo_-!7~}{wo_-!13~}{wo_-!19~}{wo_-!25~}{wo_-!31~}{wo_-!37~}{wo_-!43~}{wo_-!49~}{wo_-!55~}{wo_-!61~}{wo_-!67~}{wo_-!73~}{wo_-!79~}{wo_-!85~}{wo_-!91~}{wo_-!97~}{wo_-!103~}{wo_-!109~}{wo_-!115~}{wo_)",
        R"("20;1#1!120~$#5!40?!40K)",
        R"("20;1#6!120~)",
        R"("24;1#2!120Z$#6!48C!24^!48C)",
        R"("20;1#5!120~$#1!40?!40K)",
        R"("20;1#2!40~#5!40~#1!40~)",
        R"("20;1#5!120~$#2!60F!60w)",
        R"("20;1#5!120~$"1;1#2!18~}{wo_!74?_ow{}!18~-!24~}{wo_!62?_ow{}!24~-!30~}{wo_!50?_ow{}!30~-@BFN^!31~}{wo_!38?_ow{}!31~^NFB@-!6?@BFN^!31~}{wo_!26?_ow{}!31~^NFB@-!12?@BFN^!31~}{wo_!14?_ow{}!31~^NFB@-!18?@BFN^!31~}{wo_??_ow{}!31~^NFB@-!24?@BFN^!62~^NFB@-!30?@BFN^!50~^NFB@-!36?@BFN^!38~^NFB@-!36?_ow{}!38~}{wo_-!30?_ow{}!50~}{wo_-!24?_ow{}!62~}{wo_-!18?_ow{}!31~^NFB@??@BFN^!31~}{wo_-!12?_ow{}!31~^NFB@!14?@BFN^!31~}{wo_-!6?_ow{}!31~^NFB@!26?@BFN^!31~}{wo_-_ow{}!31~^NFB@!38?@BFN^!31~}{wo_-!30~^NFB@!50?@BFN^!30~-!24~^NFB@!62?@BFN^!24~-!18~^NFB@!74?@BFN^!18~)",
        R"("20;1#1!120~$#5!20?!80]$#2!40?!40K)",
        R"("24;1#5!120Z$#1!48C!24^!48C)",
        R"("20;1#2!120~$"1;1#6!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!13~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!7~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}-!13?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!6~-!7?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!12~-?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!18~-!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!13~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!7~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}-!13?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!6~-!7?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!12~-?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!18~-!19~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!13~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-!7~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@-~^NFB@!19?_ow{}!19~^NFB@!19?_ow{}!19~^NFB@)",
        R"("20;1#8!60~#1!60~$"1;1#6@BFN^!110~^NFB@-!6?@BFN^!98~^NFB@-!12?@BFN^!86~^NFB@-!18?@BFN^!74~^NFB@-!24?@BFN^!62~^NFB@-!30?@BFN^!50~^NFB@-!36?@BFN^!38~^NFB@-!42?@BFN^!26~^NFB@-!48?@BFN^!14~^NFB@-!54?@BFN^~~^NFB@#2-!54?_ow{}}{wo_-!48?_ow{}!12~}{wo_-!42?_ow{}!24~}{wo_-!36?_ow{}!36~}{wo_-!30?_ow{}!48~}{wo_-!24?_ow{}!60~}{wo_-!18?_ow{}!72~}{wo_-!12?_ow{}!84~}{wo_-!6?_ow{}!96~}{wo_-_ow{}!108~}{wo_)",
    });

    constexpr auto large_letters = std::to_array({
        R"("50;1#5!150~$"2;1#1!150?!145~^NFB@-!150?!139~^NFB@-!150?!133~^NFB@-!150?!127~^NFB@-!150?!121~^NFB@-!150?!115~^NFB@-!150?!109~^NFB@-!150?!103~^NFB@-!150?!97~^NFB@-!150?!91~^NFB@-!150?!85~^NFB@-!150?!79~^NFB@-!150?!76~r`-!150?!79~}{wo_-!150?!85~}{wo_-!150?!91~}{wo_-!150?!97~}{wo_-!150?!103~}{wo_-!150?!109~}{wo_-!150?!115~}{wo_-!150?!121~}{wo_-!150?!127~}{wo_-!150?!133~}{wo_-!150?!139~}{wo_-!150?!145~}{wo_)",
        R"("2;1#2!295~^NFB@-!289~^NFB@-!283~^NFB@-!277~^NFB@-!271~^NFB@-!265~^NFB@-!259~^NFB@-!253~^NFB@-!247~^NFB@-!241~^NFB@-!235~^NFB@-!229~^NFB@-!226~r`-!229~}{wo_-!235~}{wo_-!241~}{wo_-!247~}{wo_-!253~}{wo_-!259~}{wo_-!265~}{wo_-!271~}{wo_-!277~}{wo_-!283~}{wo_-!289~}{wo_-!295~}{wo_)",
        R"("60;1#1!300P$#5!300I$#2!300C)",
        R"("60;1#6!300P$#1!300M)",
        R"("50;1#1!300F$#2!300w)",
        R"("50;1#5!300~$"1;1#2!144?_ow{}~~}{wo_-!138?_ow{}!14~}{wo_-!132?_ow{}!26~}{wo_-!126?_ow{}!38~}{wo_-!120?_ow{}!50~}{wo_-!114?_ow{}!62~}{wo_-!108?_ow{}!74~}{wo_-!102?_ow{}!86~}{wo_-!96?_ow{}!98~}{wo_-!90?_ow{}!110~}{wo_-!84?_ow{}!122~}{wo_-!78?_ow{}!134~}{wo_-!72?_ow{}!146~}{wo_-!66?_ow{}!158~}{wo_-!60?_ow{}!170~}{wo_-!54?_ow{}!182~}{wo_-!48?_ow{}!194~}{wo_-!42?_ow{}!206~}{wo_-!36?_ow{}!218~}{wo_-!30?_ow{}!230~}{wo_-!24?_ow{}!242~}{wo_-!18?_ow{}!254~}{wo_-!12?_ow{}!266~}{wo_-!6?_ow{}!278~}{wo_-_ow{}!290~}{wo_-@BFN^!290~^NFB@-!6?@BFN^!278~^NFB@-!12?@BFN^!266~^NFB@-!18?@BFN^!254~^NFB@-!24?@BFN^!242~^NFB@-!30?@BFN^!230~^NFB@-!36?@BFN^!218~^NFB@-!42?@BFN^!206~^NFB@-!48?@BFN^!194~^NFB@-!54?@BFN^!182~^NFB@-!60?@BFN^!170~^NFB@-!66?@BFN^!158~^NFB@-!72?@BFN^!146~^NFB@-!78?@BFN^!134~^NFB@-!84?@BFN^!122~^NFB@-!90?@BFN^!110~^NFB@-!96?@BFN^!98~^NFB@-!102?@BFN^!86~^NFB@-!108?@BFN^!74~^NFB@-!114?@BFN^!62~^NFB@-!120?@BFN^!50~^NFB@-!126?@BFN^!38~^NFB@-!132?@BFN^!26~^NFB@-!138?@BFN^!14~^NFB@-!144?@BFN^~~^NFB@)",
        R"("50;1#1!300~$#6!50~!50?!50~!50?!50~)",
        R"("50;1#5!150~#2!150~)",
        R"("50;1#6!300~#8"15;1-"1;1!124?___oowww{{{!5}!20~!5}{{{wwwoo___-!114?__oww{{}!56~}{{wwo__-!108?_ow{}!74~}{wo_-!102?_ow{}!86~}{wo_-!99?o{}!96~}{o-!96?w}!104~}w-!93?_{!110~{_-!92?{!114~{-!91?}!116~}-!90?_!118~_-!90?@!118~@-!91?^!116~^-!92?N!114~N-!93?@N!110~N@-!96?F^!104~^F-!99?BN^!96~^NB-!102?@BFN^!86~^NFB@-!108?@BFN^!74~^NFB@-!114?@@BFFNN^!56~^NNFFB@@-!124?@@@BBFFFNNN!5^!20~!5^NNNFFFBB@@@-)",
        R"("50;1#1!300r$#5!300K)",
        R"("50;1#6!150~#1!150~)",
        R"("50;1#8!300~$#6!150F!150w)",
        R"("50;1#1!300~$"1;1#5!42~}{wo_!206?_ow{}!42~-!48~}{wo_!194?_ow{}!48~-!54~}{wo_!182?_ow{}!54~-!60~}{wo_!170?_ow{}!60~-!66~}{wo_!158?_ow{}!66~-!72~}{wo_!146?_ow{}!72~-!78~}{wo_!134?_ow{}!78~-@BFN^!79~}{wo_!122?_ow{}!79~^NFB@-!6?@BFN^!79~}{wo_!110?_ow{}!79~^NFB@-!12?@BFN^!79~}{wo_!98?_ow{}!79~^NFB@-!18?@BFN^!79~}{wo_!86?_ow{}!79~^NFB@-!24?@BFN^!79~}{wo_!74?_ow{}!79~^NFB@-!30?@BFN^!79~}{wo_!62?_ow{}!79~^NFB@-!36?@BFN^!79~}{wo_!50?_ow{}!79~^NFB@-!42?@BFN^!79~}{wo_!38?_ow{}!79~^NFB@-!48?@BFN^!79~}{wo_!26?_ow{}!79~^NFB@-!54?@BFN^!79~}{wo_!14?_ow{}!79~^NFB@-!60?@BFN^!79~}{wo_??_ow{}!79~^NFB@-!66?@BFN^!158~^NFB@-!72?@BFN^!146~^NFB@-!78?@BFN^!134~^NFB@-!84?@BFN^!122~^NFB@-!90?@BFN^!110~^NFB@-!96?@BFN^!98~^NFB@-!102?@BFN^!86~^NFB@-!102?_ow{}!86~}{wo_-!96?_ow{}!98~}{wo_-!90?_ow{}!110~}{wo_-!84?_ow{}!122~}{wo_-!78?_ow{}!134~}{wo_-!72?_ow{}!146~}{wo_-!66?_ow{}!158~}{wo_-!60?_ow{}!79~^NFB@??@BFN^!79~}{wo_-!54?_ow{}!79~^NFB@!14?@BFN^!79~}{wo_-!48?_ow{}!79~^NFB@!26?@BFN^!79~}{wo_-!42?_ow{}!79~^NFB@!38?@BFN^!79~}{wo_-!36?_ow{}!79~^NFB@!50?@BFN^!79~}{wo_-!30?_ow{}!79~^NFB@!62?@BFN^!79~}{wo_-!24?_ow{}!79~^NFB@!74?@BFN^!79~}{wo_-!18?_ow{}!79~^NFB@!86?@BFN^!79~}{wo_-!12?_ow{}!79~^NFB@!98?@BFN^!79~}{wo_-!6?_ow{}!79~^NFB@!110?@BFN^!79~}{wo_-_ow{}!79~^NFB@!122?@BFN^!79~}{wo_-!78~^NFB@!134?@BFN^!78~-!72~^NFB@!146?@BFN^!72~-!66~^NFB@!158?@BFN^!66~-!60~^NFB@!170?@BFN^!60~-!54~^NFB@!182?@BFN^!54~-!48~^NFB@!194?@BFN^!48~-!42~^NFB@!206?@BFN^!42~)",
        R"("50;1#5!300~$"25;1#1!75F!75w!75F!75w-!75F!75w!75F!75w)",
        R"("50;1#2!300~$"1;1#6~}{wo_-!7~}{wo_-!13~}{wo_-!19~}{wo_-!25~}{wo_-!31~}{wo_-!37~}{wo_-!43~}{wo_-!49~}{wo_-!55~}{wo_-!61~}{wo_-!67~}{wo_-!73~}{wo_-!79~}{wo_-!85~}{wo_-!91~}{wo_-!97~}{wo_-!103~}{wo_-!109~}{wo_-!115~}{wo_-!121~}{wo_-!127~}{wo_-!133~}{wo_-!139~}{wo_-!145~}{wo_-!151~}{wo_-!157~}{wo_-!163~}{wo_-!169~}{wo_-!175~}{wo_-!181~}{wo_-!187~}{wo_-!193~}{wo_-!199~}{wo_-!205~}{wo_-!211~}{wo_-!217~}{wo_-!223~}{wo_-!229~}{wo_-!235~}{wo_-!241~}{wo_-!247~}{wo_-!253~}{wo_-!259~}{wo_-!265~}{wo_-!271~}{wo_-!277~}{wo_-!283~}{wo_-!289~}{wo_-!295~}{wo_)",
        R"("50;1#1!300~$#5!100?!100K)",
        R"("50;1#6!300~)",
        R"("60;1#2!300Z$#6!120C!60^!120C)",
        R"("50;1#5!300~$#1!100?!100K)",
        R"("50;1#2!100~#5!100~#1!100~)",
        R"("50;1#5!300~$#2!150F!150w)",
        R"("50;1#5!300~$"1;1#2!42~}{wo_!206?_ow{}!42~-!48~}{wo_!194?_ow{}!48~-!54~}{wo_!182?_ow{}!54~-!60~}{wo_!170?_ow{}!60~-!66~}{wo_!158?_ow{}!66~-!72~}{wo_!146?_ow{}!72~-!78~}{wo_!134?_ow{}!78~-@BFN^!79~}{wo_!122?_ow{}!79~^NFB@-!6?@BFN^!79~}{wo_!110?_ow{}!79~^NFB@-!12?@BFN^!79~}{wo_!98?_ow{}!79~^NFB@-!18?@BFN^!79~}{wo_!86?_ow{}!79~^NFB@-!24?@BFN^!79~}{wo_!74?_ow{}!79~^NFB@-!30?@BFN^!79~}{wo_!62?_ow{}!79~^NFB@-!36?@BFN^!79~}{wo_!50?_ow{}!79~^NFB@-!42?@BFN^!79~}{wo_!38?_ow{}!79~^NFB@-!48?@BFN^!79~}{wo_!26?_ow{}!79~^NFB@-!54?@BFN^!79~}{wo_!14?_ow{}!79~^NFB@-!60?@BFN^!79~}{wo_??_ow{}!79~^NFB@-!66?@BFN^!158~^NFB@-!72?@BFN^!146~^NFB@-!78?@BFN^!134~^NFB@-!84?@BFN^!122~^NFB@-!90?@BFN^!110~^NFB@-!96?@BFN^!98~^NFB@-!102?@BFN^!86~^NFB@-!102?_ow{}!86~}{wo_-!96?_ow{}!98~}{wo_-!90?_ow{}!110~}{wo_-!84?_ow{}!122~}{wo_-!78?_ow{}!134~}{wo_-!72?_ow{}!146~}{wo_-!66?_ow{}!158~}{wo_-!60?_ow{}!79~^NFB@??@BFN^!79~}{wo_-!54?_ow{}!79~^NFB@!14?@BFN^!79~}{wo_-!48?_ow{}!79~^NFB@!26?@BFN^!79~}{wo_-!42?_ow{}!79~^NFB@!38?@BFN^!79~}{wo_-!36?_ow{}!79~^NFB@!50?@BFN^!79~}{wo_-!30?_ow{}!79~^NFB@!62?@BFN^!79~}{wo_-!24?_ow{}!79~^NFB@!74?@BFN^!79~}{wo_-!18?_ow{}!79~^NFB@!86?@BFN^!79~}{wo_-!12?_ow{}!79~^NFB@!98?@BFN^!79~}{wo_-!6?_ow{}!79~^NFB@!110?@BFN^!79~}{wo_-_ow{}!79~^NFB@!122?@BFN^!79~}{wo_-!78~^NFB@!134?@BFN^!78~-!72~^NFB@!146?@BFN^!72~-!66~^NFB@!158?@BFN^!66~-!60~^NFB@!170?@BFN^!60~-!54~^NFB@!182?@BFN^!54~-!48~^NFB@!194?@BFN^!48~-!42~^NFB@!206?@BFN^!42~)",
        R"("50;1#1!300~$#5!50?!200]$#2!100?!100K)",
        R"("60;1#5!300Z$#1!120C!60^!120C)",
        R"("50;1#2!300~$"1;1#6!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!49~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!43~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!37~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!31~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!25~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!19~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!13~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!7~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}-!49?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!6~-!43?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!12~-!37?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!18~-!31?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!24~-!25?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!30~-!19?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!36~-!13?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!42~-!7?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!48~-?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!54~-!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!49~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!43~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!37~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!31~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!25~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!19~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!13~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!7~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}-!49?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!6~-!43?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!12~-!37?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!18~-!31?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!24~-!25?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!30~-!19?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!36~-!13?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!42~-!7?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!48~-?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!54~-!55~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!49~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!43~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!37~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!31~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!25~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!19~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!13~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-!7~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@-~^NFB@!55?_ow{}!55~^NFB@!55?_ow{}!55~^NFB@)",
        R"("50;1#8!150~#1!150~$"1;1#6@BFN^!290~^NFB@-!6?@BFN^!278~^NFB@-!12?@BFN^!266~^NFB@-!18?@BFN^!254~^NFB@-!24?@BFN^!242~^NFB@-!30?@BFN^!230~^NFB@-!36?@BFN^!218~^NFB@-!42?@BFN^!206~^NFB@-!48?@BFN^!194~^NFB@-!54?@BFN^!182~^NFB@-!60?@BFN^!170~^NFB@-!66?@BFN^!158~^NFB@-!72?@BFN^!146~^NFB@-!78?@BFN^!134~^NFB@-!84?@BFN^!122~^NFB@-!90?@BFN^!110~^NFB@-!96?@BFN^!98~^NFB@-!102?@BFN^!86~^NFB@-!108?@BFN^!74~^NFB@-!114?@BFN^!62~^NFB@-!120?@BFN^!50~^NFB@-!126?@BFN^!38~^NFB@-!132?@BFN^!26~^NFB@-!138?@BFN^!14~^NFB@-!144?@BFN^~~^NFB@#2-!144?_ow{}}{wo_-!138?_ow{}!12~}{wo_-!132?_ow{}!24~}{wo_-!126?_ow{}!36~}{wo_-!120?_ow{}!48~}{wo_-!114?_ow{}!60~}{wo_-!108?_ow{}!72~}{wo_-!102?_ow{}!84~}{wo_-!96?_ow{}!96~}{wo_-!90?_ow{}!108~}{wo_-!84?_ow{}!120~}{wo_-!78?_ow{}!132~}{wo_-!72?_ow{}!144~}{wo_-!66?_ow{}!156~}{wo_-!60?_ow{}!168~}{wo_-!54?_ow{}!180~}{wo_-!48?_ow{}!192~}{wo_-!42?_ow{}!204~}{wo_-!36?_ow{}!216~}{wo_-!30?_ow{}!228~}{wo_-!24?_ow{}!240~}{wo_-!18?_ow{}!252~}{wo_-!12?_ow{}!264~}{wo_-!6?_ow{}!276~}{wo_-_ow{}!288~}{wo_)",
    });

    constexpr auto small_figures = std::to_array({
        R"("1;1#2!36w!9o!9_$#6!9~!9}!9{www-!63~!9}!9{!9w!9o_$#2!60~$#6!30~-"2;1!100~$#2!60~$#6!30~-"1;1!63~!9^!9N!9F!9B@$#2!60~$#6!30~-#2!36F!9B!9@$#6!9~!9^!9NFFF-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o_$#2!12?_ow{}}!8~}}{wo_-"2;1#5!100~$"1;1#2!10?_}!20~}_-!10?@^!20~^@-#5!63~!9^!9N!9F!9B@$#2!12?@BFN^^!8~^^NFB@-#5!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#1!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o_$#5!12?_ow{}}!8~}}{wo_-"2;1#1!100~$"1;1#5!10?_}!20~}_-!10?@^!20~^@-#1!63~!9^!9N!9F!9B@$#5!12?@BFN^^!8~^^NFB@-#1!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!36w!9o!9_$#2!9~!9}!9{www-#1!63~!9}!9{!9w!9o_$#5!60~$#2!30~-"2;1#1!100~$#5!60~$#2!30~-"1;1#1!63~!9^!9N!9F!9B@$#5!60~$#2!30~-#5!36F!9B!9@$#2!9~!9^!9NFFF-)",
        R"("1;1#2!36w!9o!9_$#5!34w$#2!9~!9}!9{www-!63~!9}!9{!9w!9o_$#5!34~$#2!30~-"2;1!100~$#5!30K!4~!66K-"1;1#2!63~!9^!9N!9F!9B@$#5!34~$#2!30~-!36F!9B!9@$#5!34F$#2!9~!9^!9NFFF-)",
        R"("1;1#1!54_$#6!9~!9}!9{!9w!9o!5_-#1!63~!9}!9{!9w!9o_$#6!50~-"2;1#1!100~$#6!50~-"1;1#1!63~!9^!9N!9F!9B@$#6!50~-#1!54@$#6!9~!9^!9N!9F!9B!5@-)",
        R"("1;1#8!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o_-!100~-#5!100~-!63~!9^!9N!9F!9B@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#6!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o_-!100~-#2!100~-!63~!9^!9N!9F!9B@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!36w!9o!9_$#2!34w$#5!9~!9}!9{www-!63~!9}!9{!9w!9o_$#2!34~$#5!30~-"2;1!100~$#2!30K!4~!66K-"1;1#5!63~!9^!9N!9F!9B@$#2!34~$#5!30~-!36F!9B!9@$#2!34F$#5!9~!9^!9NFFF-)",
        R"("1;1#8!54_$#5!9~!9}!9{!9w!9o!5_-#8!63~!9}!9{!9w!9o_$#5!50~-#8!100~$#5!50~-#6!100~$#2!50~-#6!63~!9^!9N!9F!9B@$#2!50~-#6!54@$#2!9~!9^!9N!9F!9B!5@-)",
    });

    constexpr auto medium_figures = std::to_array({
        R"("1;1#6!9~!9}!9{!9w!9o!9_-#2!63~!9}!9{!9w!9o!9_$#6!60~-!126}!9{!9w!9o!9_$#2!117~}}}$#6!60~-!171~!9}!9{!9woo$#2!120~$#6!60~-"4;1!200~$#2!120~$#6!60~-"1;1!171~!9^!9N!9FBB$#2!120~$#6!60~-!126^!9N!9F!9B!9@$#2!117~^^^$#6!60~-#2!63~!9^!9N!9F!9B!9@$#6!60~-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_$#2!30?_oww{{}}}!12~}}}{{wwo_-#5!171~!9}!9{!9woo$#2!25?ow{}!32~}{wo-"4;1#5!200~$"1;1#2!22?_{!42~{_-!21?_!46~_-!21?@!46~@-!22?@N!42~N@-#5!171~!9^!9N!9FBB$#2!25?BFN^!32~^NFB-#5!117~!9^!9N!9F!9B!9@$#2!30?@BFFNN^^^!12~^^^NNFFB@-#5!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#1!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_$#5!30?_oww{{}}}!12~}}}{{wwo_-#1!171~!9}!9{!9woo$#5!25?ow{}!32~}{wo-"4;1#1!200~$"1;1#5!22?_{!42~{_-!21?_!46~_-!21?@!46~@-!22?@N!42~N@-#1!171~!9^!9N!9FBB$#5!25?BFN^!32~^NFB-#1!117~!9^!9N!9F!9B!9@$#5!30?@BFFNN^^^!12~^^^NNFFB@-#1!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#2!9~!9}!9{!9w!9o!9_-#5!63~!9}!9{!9w!9o!9_$#2!60~-#1!126}!9{!9w!9o!9_$#5!117~}}}$#2!60~-#1!171~!9}!9{!9woo$#5!120~$#2!60~-"4;1#1!200~$#5!120~$#2!60~-"1;1#1!171~!9^!9N!9FBB$#5!120~$#2!60~-#1!126^!9N!9F!9B!9@$#5!117~^^^$#2!60~-#5!63~!9^!9N!9F!9B!9@$#2!60~-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#2!9~!9}!9{!9w!9o!9_-!72}!9{!9w!9o!9_$#5!63~!5}$#2!60~-!117~!9}!9{!9w!9o!9_$#5!68~$#2!60~-!171~!9}!9{!9woo$#5!68~$#2!60~-"4;1!200~$#5!60K!8~!132K-"1;1#2!171~!9^!9N!9FBB$#5!68~$#2!60~-!117~!9^!9N!9F!9B!9@$#5!68~$#2!60~-!72^!9N!9F!9B!9@$#5!63~!5^$#2!60~-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#6!9~!9}!9{!9w!9o!9_-#1!108_$#6!63~!9}!9{!9w!9o_-#1!117~!9}!9{!9w!9o!9_$#6!100~-#1!171~!9}!9{!9woo$#6!100~-"4;1#1!200~$#6!100~-"1;1#1!171~!9^!9N!9FBB$#6!100~-#1!117~!9^!9N!9F!9B!9@$#6!100~-#1!108@$#6!63~!9^!9N!9F!9B@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#8!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9woo-"2;1!200~-#5!200~-"1;1!171~!9^!9N!9FBB-!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#6!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9woo-"2;1!200~-#2!200~-"1;1!171~!9^!9N!9FBB-!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!72}!9{!9w!9o!9_$#2!63~!5}$#5!60~-!117~!9}!9{!9w!9o!9_$#2!68~$#5!60~-!171~!9}!9{!9woo$#2!68~$#5!60~-"4;1!200~$#2!60K!8~!132K-"1;1#5!171~!9^!9N!9FBB$#2!68~$#5!60~-!117~!9^!9N!9F!9B!9@$#2!68~$#5!60~-!72^!9N!9F!9B!9@$#2!63~!5^$#5!60~-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-#8!108_$#5!63~!9}!9{!9w!9o_-#8!117~!9}!9{!9w!9o!9_$#5!100~-#8!171~!9}!9{!9woo$#5!100~-"2;1#8!200~$#5!100~-#6!200~$#2!100~-"1;1#6!171~!9^!9N!9FBB$#2!100~-#6!117~!9^!9N!9F!9B!9@$#2!100~-#6!108@$#2!63~!9^!9N!9F!9B@-!9~!9^!9N!9F!9B!9@-)",
    });

    constexpr auto large_figures = std::to_array({
        R"("1;1#6!9~!9}!9{!9w!9o!9_-#2!99o!9_$#6!63~!9}!9{!9w-#2!117~!9}!9{!9w!9o!9_$#6!90~-!189{!9w!9o!9_$#2!171~!9}$#6!90~-!225~!9}!9{!9w!9o!9_$#2!180~$#6!90~-!279~!9}!9{www$#2!180~$#6!90~-"6;1!300~$#2!180~$#6!90~-"1;1!279~!9^!9NFFF$#2!180~$#6!90~-!225~!9^!9N!9F!9B!9@$#2!180~$#6!90~-!189N!9F!9B!9@$#2!171~!9^$#6!90~-#2!117~!9^!9N!9F!9B!9@$#6!90~-#2!99B!9@$#6!63~!9^!9N!9F-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9w!9o!9_$#2!48?_ooww{{{}}}!16~}}}{{{wwoo_-#5!225~!9}!9{!9w!9o!9_$#2!41?_ow{}!42~}{wo_-#5!279~!9}!9{www$#2!36?_o{}!54~}{o_-"6;1#5!300~$"1;1#2!34?w}!62~}w-!32?w!68~w-!31?_!70~_-!31?@!70~@-!32?F!68~F-!34?F^!62~^F-#5!279~!9^!9NFFF$#2!36?@BN^!54~^NB@-#5!225~!9^!9N!9F!9B!9@$#2!41?@BFN^!42~^NFB@-#5!171~!9^!9N!9F!9B!9@$#2!48?@BBFFNNN^^^!16~^^^NNNFFBB@-#5!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#1!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9w!9o!9_$#5!48?_ooww{{{}}}!16~}}}{{{wwoo_-#1!225~!9}!9{!9w!9o!9_$#5!41?_ow{}!42~}{wo_-#1!279~!9}!9{www$#5!36?_o{}!54~}{o_-"6;1#1!300~$"1;1#5!34?w}!62~}w-!32?w!68~w-!31?_!70~_-!31?@!70~@-!32?F!68~F-!34?F^!62~^F-#1!279~!9^!9NFFF$#5!36?@BN^!54~^NB@-#1!225~!9^!9N!9F!9B!9@$#5!41?@BFN^!42~^NFB@-#1!171~!9^!9N!9F!9B!9@$#5!48?@BBFFNNN^^^!16~^^^NNNFFBB@-#1!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#2!9~!9}!9{!9w!9o!9_-#5!99o!9_$#2!63~!9}!9{!9w-#5!117~!9}!9{!9w!9o!9_$#2!90~-#1!189{!9w!9o!9_$#5!171~!9}$#2!90~-#1!225~!9}!9{!9w!9o!9_$#5!180~$#2!90~-#1!279~!9}!9{www$#5!180~$#2!90~-"6;1#1!300~$#5!180~$#2!90~-"1;1#1!279~!9^!9NFFF$#5!180~$#2!90~-#1!225~!9^!9N!9F!9B!9@$#5!180~$#2!90~-#1!189N!9F!9B!9@$#5!171~!9^$#2!90~-#5!117~!9^!9N!9F!9B!9@$#2!90~-#5!99B!9@$#2!63~!9^!9N!9F-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#2!9~!9}!9{!9w!9o!9_-!108_$#5!99o___$#2!63~!9}!9{!9w-!117~!9}!9{!9w!9o!9_$#5!102~$#2!90~-!171~!9}!9{!9w!9o!9_$#5!102~$#2!90~-!225~!9}!9{!9w!9o!9_$#5!102~$#2!90~-!279~!9}!9{www$#5!102~$#2!90~-"6;1!300~$#5!90K!12~!198K-"1;1#2!279~!9^!9NFFF$#5!102~$#2!90~-!225~!9^!9N!9F!9B!9@$#5!102~$#2!90~-!171~!9^!9N!9F!9B!9@$#5!102~$#2!90~-!117~!9^!9N!9F!9B!9@$#5!102~$#2!90~-!108@$#5!99B@@@$#2!63~!9^!9N!9F-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#6!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-#1!153o!9_$#6!117~!9}!9{!9w!6o-#1!171~!9}!9{!9w!9o!9_$#6!150~-#1!225~!9}!9{!9w!9o!9_$#6!150~-#1!279~!9}!9{www$#6!150~-"6;1#1!300~$#6!150~-"1;1#1!279~!9^!9NFFF$#6!150~-#1!225~!9^!9N!9F!9B!9@$#6!150~-#1!171~!9^!9N!9F!9B!9@$#6!150~-#1!153B!9@$#6!117~!9^!9N!9F!6B-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#8!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9w!9o!9_-!225~!9}!9{!9w!9o!9_-!279~!9}!9{www-"3;1!300~-#5!300~-"1;1!279~!9^!9NFFF-!225~!9^!9N!9F!9B!9@-!171~!9^!9N!9F!9B!9@-!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#6!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-!117~!9}!9{!9w!9o!9_-!171~!9}!9{!9w!9o!9_-!225~!9}!9{!9w!9o!9_-!279~!9}!9{www-"3;1!300~-#2!300~-"1;1!279~!9^!9NFFF-!225~!9^!9N!9F!9B!9@-!171~!9^!9N!9F!9B!9@-!117~!9^!9N!9F!9B!9@-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!108_$#2!99o___$#5!63~!9}!9{!9w-!117~!9}!9{!9w!9o!9_$#2!102~$#5!90~-!171~!9}!9{!9w!9o!9_$#2!102~$#5!90~-!225~!9}!9{!9w!9o!9_$#2!102~$#5!90~-!279~!9}!9{www$#2!102~$#5!90~-"6;1!300~$#2!90K!12~!198K-"1;1#5!279~!9^!9NFFF$#2!102~$#5!90~-!225~!9^!9N!9F!9B!9@$#2!102~$#5!90~-!171~!9^!9N!9F!9B!9@$#2!102~$#5!90~-!117~!9^!9N!9F!9B!9@$#2!102~$#5!90~-!108@$#2!99B@@@$#5!63~!9^!9N!9F-!9~!9^!9N!9F!9B!9@-)",
        R"("1;1#5!9~!9}!9{!9w!9o!9_-!63~!9}!9{!9w!9o!9_-#8!153o!9_$#5!117~!9}!9{!9w!6o-#8!171~!9}!9{!9w!9o!9_$#5!150~-#8!225~!9}!9{!9w!9o!9_$#5!150~-#8!279~!9}!9{www$#5!150~-"3;1#8!300~$#5!150~-#6!300~$#2!150~-"1;1#6!279~!9^!9NFFF$#2!150~-#6!225~!9^!9N!9F!9B!9@$#2!150~-#6!171~!9^!9N!9F!9B!9@$#2!150~-#6!153B!9@$#2!117~!9^!9N!9F!6B-!63~!9^!9N!9F!9B!9@-!9~!9^!9N!9F!9B!9@-)",
    });

}  // namespace

namespace flags {

    std::string_view small(const char c)
    {
        if (c >= 'A' && c <= 'Z')
            return small_letters[c - 'A'];
        else if (c >= '0' && c <= '9')
            return small_figures[c - '0'];
        else
            return "";
    }

    std::string_view medium(const char c)
    {
        if (c >= 'A' && c <= 'Z')
            return medium_letters[c - 'A'];
        else if (c >= '0' && c <= '9')
            return medium_figures[c - '0'];
        else
            return "";
    }

    std::string_view large(const char c)
    {
        if (c >= 'A' && c <= 'Z')
            return large_letters[c - 'A'];
        else if (c >= '0' && c <= '9')
            return large_figures[c - '0'];
        else
            return "";
    }

}  // namespace flags
