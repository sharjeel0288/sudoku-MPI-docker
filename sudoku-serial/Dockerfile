FROM gcc:latest
COPY . /user/src/c_test
WORKDIR /user/src/c_test
RUN make
CMD ["./sudoku-solver"]


# to compile 
# "docker build -t gcc-docker ."

# to run 
#  docker run -ti --rm gcc-docker ./sudoku-solver  ./Sudoku_Testcases/16x16_board/sudoku16_input1