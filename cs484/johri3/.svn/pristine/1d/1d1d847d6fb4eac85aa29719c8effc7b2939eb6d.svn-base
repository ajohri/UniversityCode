RM := rm -rf

HEADERS = gs-helper.h
OBJS = gs-helper.o gs.o

all: gs

gs: $(OBJS)
	@echo 'Building target: $@'
	gcc -O2 -fopenmp -o "./gs" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

%.o: %.c $(HEADERS)
	gcc -O2 -fopenmp -c $< -o $@

clean:
	-$(RM) $(OBJS)
	-$(RM) ./gs
	-@echo ' '

.PHONY: all clean dependents directories
.SECONDARY:
