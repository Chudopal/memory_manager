#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "memory.h"

m_id find_free_segment(int);

struct virtual_memory memory;

m_id m_malloc(int size_of_chunk, m_err_code* error) {
    
    m_id segment = find_free_segment(size_of_chunk);
    
    if (segment == NULL) defragmentation();
    
    segment = find_free_segment(size_of_chunk);

    if (segment == NULL){
        *error = M_ERR_ALLOCATION_OUT_OF_MEMORY;
        return NULL;
    }
}


m_id find_free_segment(int size_of_chunk){
    for (int i = 0; i < memory.number_of_pages; i++){
        m_id current = (memory.pages + i) -> begin;
        
        if (!current->is_used){
            
            current -> size = size_of_chunk;
            current -> next = current + current -> size;
            current -> not_calling = 0;
            current -> is_used = true;
            
            return current;
        
        } else {
            
            while(current->is_used){
                current = current -> next;
            }
            if !(current >= (memory.pages + i) -> begin){
                current -> size = size_of_chunk;
                current -> next = current + current -> size;
                current -> not_calling = 0;
                current -> is_used = true;

                return current;
            } 
        }
    }
    return NULL;
}


void m_free(m_id ptr, m_err_code* error) {
    
}


void m_read(m_id read_from_id,void* read_to_buffer, int size_to_read, m_err_code* error) {
    
}


void m_write(m_id write_to_id, void* write_from_buffer, int size_to_write, m_err_code* error) {
    
}


void m_init(int number_of_pages, int size_of_page, int temporary_locality) {
    
    struct page_frame * pages;

    pages = (struct page_frame*) malloc(number_of_pages * sizeof(struct page_frame));
    
    for(int i = 0; i < number_of_pages; i++){
        (pages + i) -> size = size_of_page;
        (pages + i) -> begin = malloc(pages -> size);
        (pages + i) -> begin -> size = size_of_page;
        (pages + i) -> begin -> is_used = false;
        (pages + i) -> begin -> next = NULL;
    }
    
    memory.pages = pages;
    memory.temporary_locality = temporary_locality;
    memory.number_of_pages = number_of_pages;
}

void defragmentation(){}