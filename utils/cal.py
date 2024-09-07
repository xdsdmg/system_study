"""
Number base conversion
Author: xdsdmg@163.com
Date: 2024-08-19 19:59
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

if __name__ == "__main__":
    # 从命令行参数中获取十六进制字符串
    hex_str = sys.argv[1]

    # 将十六进制字符串转换为十进制整数
    decimal_num = int(hex_str, 16)

    print(decimal_num)
