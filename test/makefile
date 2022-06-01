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
	./sct.exe ztrans > testout_ztrans.txt
	./sct.exe pwm > testout_pwm.txt
	./sct.exe pwmsin > testout_pwmsin.txt
	./sct.exe rkflt > testout_rkflt.txt
	./sct.exe transab > testout_transab.txt
	./sct.exe transdq > testout_transdq.txt

#テスト対象のオブジェクトファイル作成
TARGET:
	make -C ../

# リンク
# $@ ターゲットファイル（ここでは target.exe)名
$(OUT): $(OBJ)
	$(CC) $(OBJ) $(TARGET_OBJS) -o $@

#exeを削除
.PHONY : del
del:
	$(RM) sct.exe

#オブジェクトファイルをすべて削除
.PHONY : clean
clean:
	$(RM) sct.exe
	$(RM) obj/sct.o
	$(RM) ../obj/*.o
