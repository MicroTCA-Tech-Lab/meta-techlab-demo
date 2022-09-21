
.PHONY: all
all: irq_handler_demo

irq_handler_demo: irq_handler_demo.c custom_irq_gen.c
	$(CC) $^ -o $@ $(LDFLAGS) -Wall -Wextra -pedantic

clean:
	rm -f irq_handler_demo
