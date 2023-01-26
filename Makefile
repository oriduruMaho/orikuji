VERSION := 0.0.1	# バージョン
TARGET := orikuji	# バージョン情報を含む実行ファイルの名前
CC := hgcc	# コンパイラを指定する
CFLAGS := -Wall -I "./include"	# コンパイラに与えるオプションを指定する

# デフォルト（makeにオプションを与えなかったとき）のターゲット
%: $(TARGET)

# 最終成果物をつくるタスク
$(TARGET): orikuji.c
	$(CC) $(CFLAGS) -o $@ $^

# 最終成果物を（なかったら作って）実行するタスク
run: $(TARGET)
	./$(TARGET)

# コンパイルした実行ファイルとかを削除するコマンド
.PHONY: clean
clean:
	-rm ./$(TARGET)
	-rm ./*.o