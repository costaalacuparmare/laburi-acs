.PHONY: build run clean

build:
	@echo "Nothing to build"

run:
	python3 MyBot.py

archive_etapa1:
	zip -r archive.zip MyBot.py hlt.py utils/ Makefile .gitignore run_local.sh

clean:
	rm -rf __pycache__
