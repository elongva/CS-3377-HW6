# Einar Longva (evl130030)
# CS3377.501

CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
CPPFLAGS = -I/scratch/perkins/include
LDFFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

PROJECTNAME = TestCDKfile

EXEC = cdkTest

SRCS = cdk.cc

OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)

Makefile:	$(SRCS:.cc=.d)

%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(EXEC):$(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFFLAGS) $(LDLIBS)

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date + '%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
