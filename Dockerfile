FROM gcc:4.9
COPY ./src /usr/src/emm
WORKDIR /usr/src/emm
RUN g++ -c *.cpp && g++ *.o -o emm
CMD ["./emm"]