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
    おみくじをtxtファイルに出力するメインプロクラム
    """

    current_directory = os.getcwd()
    text_file = current_directory + os.sep + 'fortune.txt'
    script_file = current_directory + os.sep + 'YourOrikuji.txt'

    omikuji_messege = read_file(text_file)
    messege_list = make_fortune_messeges(omikuji_messege)
    script_list = make_omikuji(messege_list)
    write_file(script_file, script_list)

    return 0

def read_file(file_name):
    """
    ファイルを読み込んで、おみくじのメッセージをリストに入れる
    """

    fortune_messeges = []

    #ファイルを読み込む
    with open(file_name, 'r', encoding='utf-8') as file:
        for a_line in file:
            a_string = a_line.split()
            fortune_messeges.append(a_string)
        #print(fortune_messeges)
    return fortune_messeges

def make_fortune_messeges(messege_list):
    """
    文字列を並び替えておみくじの内容を縦書きに見えるようなリストを作る
    """

    fortune_messege = random.sample(messege_list, 3)
    word_list = []
    script_list = []

    for omikuji_messege in fortune_messege:
        for a_messege in omikuji_messege:
            a_list = list(a_messege)
        word_list.append(a_list)

    word_list_first, word_list_second, word_list_thired = word_list

    max_word_namber = max(len(word_list_first), len(word_list_second), len(word_list_thired))

    word_list_first = padding(word_list_first, max_word_namber)
    word_list_second = padding(word_list_second, max_word_namber)
    word_list_thired = padding(word_list_thired, max_word_namber)

    for word_first, word_second, word_thired in zip(word_list_first, word_list_second, word_list_thired):
        script_list.append('\x20'+'\x20'.join([word_first, word_second, word_thired]))

    return script_list
    

def padding(word_list, number):
    """
    文字数を揃えるために＊を追加する
    """
    while number!=len(word_list):
        word_list.append('＊')
    
    return word_list


def make_omikuji(omikuji_messege):
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
    script_list.append('\n'.join(omikuji_messege))
    script_list.append(line)
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
