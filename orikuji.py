#!/user/bin/env python
# -*- coding: utf-8 -*-

"""
おみくじを引くだけのプログラム
"""

__author__ = 'oriduru Maho'

import os
import random
import datetime


def main():
    """
    
    """

    current_directory = os.getcwd()
    text_file = current_directory + os.sep + 'fortune.txt'
    script_file = current_directory + os.sep + 'YourFortune.txt'

    #read_file(text_file)
    script_list = make_omikuji()
    write_file(script_file, script_list)

    return 0

#def read_file(file_name):
    """
    ファイルを読み込んで、おみくじのメッセージをリストに入れる
    """


    fortune_messeges = []
    #ファイルを読み込む
    with open(file_name, 'r', encoding='utf-8') as file:
        for a_line in file:
            a_string = a_line.split()[0]
            fortune_messeges.append(a_string)

    return fortune_messeges

#def make_fortune_messeges(messege_list):
    """

    

    fortune_messege = random.sample(messege_list, 3)

    string_list = fortune_messege.split()"""



def make_omikuji():
    """
    おみくじのテキストファイルに書かれるスクリプトのリストを作る
    """
    omikuji_list = ["大吉", "中吉", "小吉", "末吉", "吉", "凶", "大凶"]

    line = '---------'
    dot = '...'

    script_list = []

    today = datetime.date.today().strftime("%Y年%m月%d日")
    now = datetime.datetime.now().strftime("%H時%M分%S秒")

    script_list.append(f'# このおみくじは{today}{now}にプログラムによって作られました')
    script_list.append('')

    script_list.extend([line, dot+random.choice(omikuji_list)+dot,'========='])
    script_list.append('')


    

    return script_list

def write_file(file_name, script_list):
    """"
    file_nameで指定されたファイルに、script_listで指定したリストの各要素を結合して書き出す
    file_nameがNoneの場合は標準出力に書き出す。常にNoneを応答する。
    """

    a_string = "\n".join(script_list)
    if file_name is None:
        print(a_string)
    else:
        #ファイルに書き出す
        with open(file_name, 'w', encoding="utf-8") as a_file:
            a_file.write(a_string)


if __name__ == '__main__':
    import sys
    sys.exit(main())