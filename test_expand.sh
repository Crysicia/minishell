#!/bin/bash

./Minishell -c 'echo bonjour'
bash -c 'echo bonjour'

./Minishell -c 'echo bon"jour'
bash -c 'echo bon\"jour'

./Minishell -c 'echo $USER$PWD'
bash -c 'echo $USER$PWD'

./Minishell -c "echo bon\"jour $USER"
bash -c 'echo bon\"jour $USER'

valgrind ./Minishell -c "echo \"bonjour\"\""
bash -c 'echo \"bonjour\"\"'

./Minishell -c "echo \"bonjour\"\""
bash -c 'echo \"bonjour\"\"'
