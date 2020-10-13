/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
    char* video_memory = (char*) 0xb8000;
    char message[] = "Kostas";
    for (int i = 0; i < 6; i++){
        video_memory[i*2] = message[i];
    }



}
