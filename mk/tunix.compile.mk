%.o: %.c $(HEADERS)
	$(CC) $(ARCHFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.cc $(HEADERS)
	$(CXX) $(ARCHFLAGS) $(CXXFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $< -f elf -o $@

%.bin: %.asm
	$(ASM) $< -f bin -o $@