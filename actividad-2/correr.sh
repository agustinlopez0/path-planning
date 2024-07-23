# make clean && \
make robot && \
# 
make sensor && \
mkfifo feedback && \
(valgrind ./robot < feedback | ./sensor $1 > feedback ; \
rm feedback)