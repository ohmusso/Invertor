#Cコンパイラ
CC=gcc

#オブジェクトディレクトリ
OBJDIR=obj

#ソースファイル
SRCS=$(wildcard *.c)

#オブジェクトファイル
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

#コンパイルオプション
#CFLAGS=-Wall -O3	#-Wall はワーニングを表示、 -O3 は最適化オプション
CFLAGS=-Wall

#削除コマンド
RM=del

#分割コンパイル(オブジェクトファイル作成）
# $@ ターゲットファイル名
# $< 最初の依存関係の名前
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

#デフォルトターゲット
.PHONY : all
all: $(OBJS)

#オブジェクトファイルをすべて削除
.PHONY : clean
clean:
	$(RM) $(OBJS)
