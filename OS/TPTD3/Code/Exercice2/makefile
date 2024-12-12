#----- Fichier genere automatiquement sous Linux ------
#----- Fri Nov 29 03:56:43 PM CET 2024

#-----
INCDIR=.
CCFLAGS=-W -Wall -Werror  -pedantic -I$(INCDIR) -I.
LDFLAGS= 
DEPOPT=-M
CCC=gcc
#-----

#-------------  Appli  --------------

TARGET=nbOctets

FILESnbOctets=nbOctets.c \
	partage.c

LDFLAGSnbOctets=$(LDFLAGS) 

OBJECTSnbOctets=$(FILESnbOctets:.c=.o)

#-------------  Appli  --------------

all: $(TARGET)
#-------------  Appli  --------------

nbOctets : $(OBJECTSnbOctets)
	$(CCC) $(OBJECTSnbOctets) \
		-o nbOctets $(LDFLAGSnbOctets)
#------------------------------------

.c.o :
	$(CCC) $(CCFLAGS) -c $< \
		-o $*.o
 
dep :
	@echo "======== Mise a jour des dependances : .depend ========"
	@rm -f .depend
	@for i in *.c ; do \
	echo $$i ; \
	$(CCC) $(DEPOPT) $(CCFLAGS) $$i > .tmpdepend ; \
	OBJNAME=`echo $$i | sed -e s%\\\.c%.o% ` ; \
	cat .tmpdepend | \
	sed -e s%`basename $$i .c`\\\.o%$$OBJNAME%         >> .depend ; \
	echo  >> .depend ; \
	done
	@rm -f .tmpdepend
 
CLEANING=rm -f *.o core a.out $(TARGET) *.exe .depend
CONSEIL=echo Penser a faire : make -f makefile dep
 
clear :
	@$(CLEANING)
	@echo
	@$(CONSEIL)
	@echo
clean :
	$(CLEANING)
	@echo
	@$(CONSEIL)
	@echo

sinclude .depend

