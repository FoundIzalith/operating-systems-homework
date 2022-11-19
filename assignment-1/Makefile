all: run

producer: producer.c
	gcc producer.c -pthread -lrt -o producer

consumer: consumer.c
	gcc consumer.c -pthread -lrt -o consumer

run: producer consumer
	./producer && ./consumer

clean:
	rm producer
	rm consumer 