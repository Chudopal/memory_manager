#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "memory.h"

m_id find_free_segment(int);
void defragmentation();

struct virtual_memory memory;

//-------------------------------------------------------------------------------------------------
m_id m_malloc(int size_of_chunk, m_err_code* error) {
    
    m_id segment = find_free_segment(size_of_chunk);
    
    if (segment == NULL) defragmentation();
    
    segment = find_free_segment(size_of_chunk);

    if (segment == NULL){
        *error = M_ERR_ALLOCATION_OUT_OF_MEMORY;
        return NULL;
    }
}

//-------------------------------------------------------------------------------------------------
m_id find_free_segment(int size_of_chunk){
    for (int i = 0; i < memory.number_of_pages; i++){
        bool is_oversize = false;

        m_id current = (memory.pages + i) -> begin;
        
        while(current->is_used || current->size <= size_of_chunk){
            current = current -> next;
            if (current >=  (memory.pages + i) -> begin + (memory.pages + i) -> size) {
                is_oversize = true;
                break;
            }
        }

        if (!is_oversize) {
            if (current->next == NULL){
                current -> next = current + size_of_chunk;
                current -> next -> next = NULL;
                current -> next -> size = current -> size - size_of_chunk;
            }else{

                if (current -> size != size_of_chunk){
                    m_id next = current + size_of_chunk;
                    next->size = current->size - size_of_chunk;
                    next->next = current->next;
                    next->is_used = false;
                    current -> next = next;
                }
            }

            current -> size = size_of_chunk;
            current -> not_calling = 0;
            current -> is_used = true;
            return current;
        }
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------
void m_free(m_id ptr, m_err_code* error) {
    ptr -> is_used = false;
}

//-------------------------------------------------------------------------------------------------
void m_read(m_id read_from_id,void* read_to_buffer, int size_to_read, m_err_code* error) {
    read_from_id -> not_calling = 0;
    memcpy(read_to_buffer, read_from_id, size_to_read);
    *error = M_ERR_OK;
    for (int i = 0; i < memory.number_of_pages; i++){
        m_id current = (memory.pages+i) -> begin;
        while(current != NULL){
            if (current != read_from_id){
                (current -> not_calling)++;
            }
            current = current -> next;
        }
    }
}

//-------------------------------------------------------------------------------------------------
void m_write(m_id write_to_id, void* write_from_buffer, int size_to_write, m_err_code* error) {
    memcpy(write_to_id, write_from_buffer, size_to_write);
    *error = M_ERR_OK;
}

//-------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------
void defragmentation(){
    for (int i = 0; i < memory.number_of_pages; i++){//страницы
        
        m_id current = (memory.pages + i) -> begin;
        
        while(current -> next != NULL){//идем по блокам
            
            if (!current->is_used){
                
                m_id empty_block = current;
                int size_of_empty_block = 0;
                
                while(!empty_block -> is_used){// множество пустых блоков
                    
                    size_of_empty_block += current -> size;
                    empty_block = empty_block -> next;                
                }

                m_id temp_buffer = empty_block;
                
                current -> size = temp_buffer -> size;
                current -> is_used = true;
                current -> data = temp_buffer -> data;
                current -> not_calling = temp_buffer -> not_calling;

                m_id next = current + current -> size;
                next -> size = size_of_empty_block;
                next -> next = empty_block -> next;

                current -> next = next;
            }
            current = current -> next;
       }
    }
}