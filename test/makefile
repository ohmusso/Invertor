#mingw32-make

#Powershell
SHELL       := powershell.exe
.SHELLFLAGS := -NoProfile -Command

#Cコンパイラ
CC=gcc

#テスト関数
OBJDIR=obj
SRC=sct.c
OBJ=$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#テスト対象のオブジェクト
TARGET_OBJS=$(wildcard ../obj/*.o)
#作成する実行ファイル
OUT=sct.exe

#コンパイルオプション
#CFLAGS=-Wall -O3	#-Wall はワーニングを表示、 -O3 は最適化オプション
CFLAGS=-Wall

#削除コマンド
RM=del

#テスト関数のオブジェクトファイル作成
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $<

#デフォルトターゲット
.PHONY : all
all: TARGET $(OUT)
	./sct.exe > out.txt

#テスト対象のオブジェクトファイル作成
TARGET:
	make -C ../

# リンク
# $@ ターゲットファイル（ここでは target.exe)名
$(OUT): $(OBJ)
	$(CC) $(OBJ) $(TARGET_OBJS) -o $@

#オブジェクトファイルをすべて削除
.PHONY : clean
clean:
	$(RM) sct.exe
	$(RM) obj/sct.o
	$(RM) ../obj/*.o
