# make clean && \
make robot && \
# 
make sensor && \
mkfifo feedback && \
(./robot < feedback | ./sensor $1 > feedback ; \
rm feedback)