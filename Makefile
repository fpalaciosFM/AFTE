RE = RegExpr
BO = Node\BinOp
N = Node
LTX = Latex

objects = Main.o \
	$(RE)\Parser.o $(RE)\RegExpr.o \
	$(BO)\BinOp.o $(BO)\Closure.o $(BO)\Concatenation.o $(BO)\Union.o \
	$(N)\Node.o $(N)\Empty.o $(N)\Lambda.o $(N)\Letter.o \
	$(LTX)\Latex.o \

prog : $(objects)
	g++ -o prog $(objects)

include $(RE)\$(RE).mk
include $(BO)\BinOp.mk
include $(N)\$(N).mk
include $(LTX)\$(LTX).mk

clean :
	del prog.exe $(objects)