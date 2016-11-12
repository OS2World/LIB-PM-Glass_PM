#
# makefile for the whole pm library package
#

!include config\makerules

PARTS = pmlib

all: $(PARTS) $(MDUMMY)

pmlib:  $(MDUMMY)
	cd source
	@$(MAKE) $(MFLAGS)
	@cd ..

clean:	$(MDUMMY)
	cd source
	@$(MAKE) $(MFLAGS) clean
	@cd ..
