
DOC_DIR 	= doc
DOXYGEN 	= doxygen
DOXYGEN_DIR = doxygen
DOXYFILE 	= $(DOC_DIR)/doxygen.config

default:
	make -C src

clean: dox_clear
	make -C src clean

dox: $(DOXYFILE) $(SOURCES) $(HEADERS) README.md
	(cd $(DOC_DIR); rm -rf $(DOXYGEN_DIR);)
	$(DOXYGEN) $(DOXYFILE)
	mv $(DOXYGEN_DIR) $(DOC_DIR)

dox_clear:
	cd $(DOC_DIR); rm -rf $(DOXYGEN_DIR)
