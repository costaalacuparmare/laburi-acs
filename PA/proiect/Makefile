.PHONY: build run clean

build:
	@echo "Nothing to build"

run:
	python3 MyBot.py

archive_etapa1:
	zip -r etapa1.zip MyBot.py hlt.py utils/ Makefile .gitignore run_local.sh

archive_etapa2:
	zip -r etapa2.zip MyBot.py hlt.py utils/ Makefile .gitignore run_local.sh

archive_etapa3:
	zip -r etapa3.zip MyBot.py hlt.py utils/ Makefile .gitignore run_local.sh

clean:
	rm -rf __pycache__
