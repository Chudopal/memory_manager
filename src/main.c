#include <stdlib.h>
#include <stdio.h>

#include "memory/memory.h"

int main(int argc, char **argv) {


    m_init(5, 4096, 10);

    int error_code;

    m_id chunk_1 = m_malloc(10, error_code);
    m_id chunk_2 = m_malloc(10, error_code);
    m_id chunk_3 = m_malloc(10, error_code);

    m_free(chunk_2, error_code);

    printf("This is chunk_2 %p\n", chunk_2);
    printf("This is chunk_2 -> next %p\n", chunk_2 -> next);

    m_id chunk_2_1 = m_malloc(4, error_code);
    m_id chunk_2_2 = m_malloc(6, error_code);


    printf("chunk_1 - %p\n", chunk_1);
    printf("chunk_1 -> next - %p\n", chunk_1->next);
    printf("chunk_2_1 - %p\n", chunk_2_1);
    printf("chunk_2_1 -> next - %p\n", chunk_2_1->next);
    printf("chunk_2_2 - %p\n", chunk_2_2);
    printf("chunk_2_2 -> next - %p\n", chunk_2_2->next);
    printf("chunk_3 - %p\n", chunk_3);
    printf("chunk_3 -> next - %p\n", chunk_3->next);



    /*int error_code;
    m_id chunk_1 = m_malloc(13, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_id chunk_2 = m_malloc(20, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_id chunk_3 = m_malloc(50, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_id chunk_1 = m_malloc(13, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_id chunk_2 = m_malloc(20, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_id chunk_3 = m_malloc(50, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_write(chunk_1, "Hello World!", 13, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_write(chunk_2, "Operating Systems", 18, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_write(chunk_3, "Super dumb memory allocator", 28, &error_code);
    if (error_code != M_ERR_OK) abort();

    char buffer[50];

    m_read(chunk_1, buffer, 13, &error_code);
    if (error_code != M_ERR_OK) abort();
    printf("%s\n", buffer);

    m_read(chunk_2, buffer, 18, &error_code);
    if (error_code != M_ERR_OK) abort();
    printf("%s\n", buffer);

    m_read(chunk_3, buffer, 28, &error_code);
    if (error_code != M_ERR_OK) abort();
    printf("%s\n", buffer);

    m_free(chunk_1, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_free(chunk_2, &error_code);
    if (error_code != M_ERR_OK) abort();

    m_free(chunk_3, &error_code);
    if (error_code != M_ERR_OK) abort();*/

}