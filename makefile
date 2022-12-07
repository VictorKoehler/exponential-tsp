CPLEX_VERSION = 12.8

#detecta se o sistema é de 32 ou 64 bits
N_BITS = $(shell getconf LONG_BIT)
ifeq ($(N_BITS),32)
   ifeq ($(CPLEX_VERSION), 12.4)
      SYSTEM  = x86_sles10_4.1
   else
      SYSTEM = x86_linux
   endif
   BITS_OPTION = -m32
else
   ifeq ($(CPLEX_VERSION), 12.4)
      SYSTEM  = x86-64_sles10_4.1
   else
      SYSTEM = x86-64_linux
   endif
   BITS_OPTION = -m64
endif


LIBFORMAT = static_pic

####diretorios com as libs do cplex
ifeq ($(CPLEX_VERSION), 12.4)
   CPLEXDIR  = /opt/cplex/cplex
   CONCERTDIR = /opt/cplex/concert
else
   CPLEXDIR  = /opt/cplex/cplex
   CONCERTDIR = /opt/cplex/concert
endif
   
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

#### define o compilador
CPPC = g++
ifeq ($(DEBUG), 1)
    CCOPTFLAGS = -g3 -Wall -Wextra -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=null -fsanitize=signed-integer-overflow
else
    CCOPTFLAGS = -O2 -DNDEBUG
endif
#############################

#### opcoes de compilacao e includes
#CCOPT = $(BITS_OPTION) -O3 -g -fPIC -fexceptions -DNDEBUG -DIL_STD -std=c++0x -fpermissive
#CCOPT = $(BITS_OPTION) -O3 -g3 -fPIC -fexceptions -DNDEBUG -DIL_STD -std=c++0x -fpermissive -fno-strict-aliasing
CCOPT = $(BITS_OPTION) $(CCOPTFLAGS) -m64 -fPIC -fno-strict-aliasing -fexceptions -DIL_STD -std=c++17
CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)
#############################

#### flags do linker
#CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -lpthread -lGL -lGLU -lglut -lboost_program_options

CCLNFLAGS = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR) $(CCOPTFLAGS) -lm -lpthread -lconcert -lilocplex -lcplex -lm -lpthread -ldl
#############################

#### diretorios com os source files e com os objs files
SRCDIR = src
ifdef $(OBJDIR)
   OBJDIR = $(OBJDIR)
else
   ifeq ($(DEBUG), 1)
      OBJDIR = obj/debug
   else
      OBJDIR = obj
   endif
endif
#############################

#### lista de todos os srcs e todos os objs
SRCS = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
#############################

#### regra principal, gera o executavel
mlCut: $(OBJS) 
	@echo  "\033[31m \nLinking all objects files: \033[0m"
	$(CPPC) $(BITS_OPTION) $(OBJS) -o $(OBJDIR)/$@ $(CCLNFLAGS)
############################

#inclui os arquivos de dependencias
-include $(OBJS:.o=.d)

#regra para cada arquivo objeto: compila e gera o arquivo de dependencias do arquivo objeto
#cada arquivo objeto depende do .c e dos headers (informacao dos header esta no arquivo de dependencias gerado pelo compiler)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p "$(shell dirname $@)"
	@echo  "\033[31m \nCompiling $<: \033[0m"
	$(CPPC) $(CCFLAGS) -c $< -o $@
	@echo  "\033[32m \ncreating $< dependency file: \033[0m"
	$(CPPC) $(CCFLAGS) -std=c++0x -MM $< > $(basename $@).d
	@mv -f $(basename $@).d $(basename $@).d.tmp #proximas tres linhas colocam o diretorio no arquivo de dependencias (g++ nao coloca, surprisingly!)
	@sed -e 's|.*:|$(basename $@).o:|' < $(basename $@).d.tmp > $(basename $@).d
	@rm -f $(basename $@).d.tmp

#delete objetos e arquivos de dependencia
clean:
	@echo "\033[31mcleaning obj directory \033[0m"
	@find $(OBJDIR)/ -name '*.o' -exec rm -r {} \;
	@find $(OBJDIR)/ -name '*.d' -exec rm -r {} \;
	@rm -f $(OBJDIR)/solver

rebuild: clean solver
