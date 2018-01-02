/**
 * Ideal Indirection Lab
 * CS 241 - Spring 2016
 */
#include <stdio.h>
#include "mmu.h"
#include "kernel.h"
#define vpn1_mask 0x0007ff8000000000                                      // This is the mask that I will and with the virtual address to get VPN1
#define vpn2_mask 0x0000007ff8000000                                      // This is the mask that I will and with the virtual address to get VPN2
#define vpn3_mask 0x0000000007ff8000                                      // This is the mask that I will and with the virtual address to get VPN3
#define offset_mask 0x0000000000007fff                                    // This is the mask that I will and with the virtual address to get the offset

MMU *MMU_create() {
  MMU *mmu = calloc(1, sizeof(MMU));
  PageTable **base_pts = mmu->base_pts;
  for (size_t i = 0; i < MAX_PROCESS_ID; i++) {
    base_pts[i] = PageTable_create();
  }
  mmu->tlb = TLB_create();
  return mmu;
}

void *MMU_get_physical_address(MMU *mmu, void *virtual_address, size_t pid) {
  
  long vpn1, vpn2, vpn3, offset, tlb_value;                               // Creating VPN variables to store the addresses.
  void * key;
  void    *phy_addr;
  PageTable *pt1, *pt2, *pt3, *base;

  vpn1 = ((long)virtual_address & vpn1_mask) >> 39;                       // Using the bitwise and operator and then shifting the necessary values over.
  vpn2 = ((long)virtual_address & vpn2_mask) >> 27;
  vpn3 = ((long)virtual_address & vpn3_mask) >> 15;
  offset = ((long)virtual_address & offset_mask);
  tlb_value = ((long)virtual_address & (vpn1_mask | vpn2_mask | vpn3_mask)) >> 15;

  //printf("MMU_Get_Physical_Address: TLB_Value - Key:%p\n", (void *)tlb_value);

  key = (void *)tlb_value;

  phy_addr = TLB_get_physical_address(&(mmu->tlb), key, pid);             // Checking to see if the address has already been sotred in the TLB

  if(phy_addr)                                                            // We have found the physical memory in the TLB          
    return ((char *)phy_addr+offset);
  else
    MMU_tlb_miss(mmu, virtual_address, pid);                              // We did not find the physical memory in the TLB now we need to go through the page tables.

  base = mmu->base_pts[pid];                                              // First level traversal through the entire tree structure(Base array).
  pt1 = PageTable_get_entry(base, vpn1);
  if (pt1) {                                                              // Second level traversal through the entire tree structure(First level page table).          
      pt2 = PageTable_get_entry(pt1, vpn2);
      if (pt2) {                                                          // Third level traversal through the entire tree structure(Second level page table).
        pt3 = PageTable_get_entry(pt2, vpn3);
        if (pt3) {                                                        // Fourth level traversal through the entire tree structure(Third level page table).
          TLB_add_physical_address(&(mmu->tlb), key, pid, pt3);           // Getting the frame here.
          return ((char *)pt3 +offset); 
        } 
        else {                                                            // If the address pointed to null in the third level page table.
                                                                          // Need to create one level of page table now.
                                                                          // Raise page fault but the number of creates and asks_kernel_for_frame = 1
          MMU_raise_page_fault(mmu, virtual_address, pid);

          pt3 = ask_kernel_for_frame();
          PageTable_set_entry(pt2, vpn3, pt3);
      
          // Add the entry to the TLB
          TLB_add_physical_address(&(mmu->tlb), key, pid, pt3);
          

          return ((char *)pt3 +offset); 
        }
      } else {                                                            // If the address pointed to null in the second level page table. 
                                                                          // Need to create two levels of page tables now.     
        // Raise page fault but the number of creates and asks_kernel_for_frame = 2
        MMU_raise_page_fault(mmu, virtual_address, pid);
        MMU_raise_page_fault(mmu, virtual_address, pid);

        pt2 = PageTable_create();
        pt3 = ask_kernel_for_frame();
        PageTable_set_entry(pt1, vpn2, pt2);
        PageTable_set_entry(pt2, vpn3, pt3);

        // Add the entry to the TLB
        TLB_add_physical_address(&(mmu->tlb), key, pid, pt3);

        return((char *)pt3 +offset);
      }
  } else {                                                                // If the address pointed to null in the first level page table.
                                                                          // Need to create three levels of page tables now.
      // Raise page fault but the number of creates and asks_kernel_for_frame = 3
      MMU_raise_page_fault(mmu, virtual_address, pid);
      MMU_raise_page_fault(mmu, virtual_address, pid);
      MMU_raise_page_fault(mmu, virtual_address, pid);

      pt1 = PageTable_create();
      
      PageTable_set_entry(base, vpn1, pt1);
      pt2 = PageTable_create();
      pt3 = ask_kernel_for_frame();
      PageTable_set_entry(pt1, vpn2, pt2);
      PageTable_set_entry(pt2, vpn3, pt3);

      

      // Add the entry to the TLB
      TLB_add_physical_address(&(mmu->tlb), key, pid, pt3);

      return((char *)pt3 +offset);
  }
  

  return NULL;
}

void MMU_tlb_miss(MMU *mmu, void *address, size_t pid) {
  mmu->num_tlb_misses++;
  printf("Process [%lu] tried to access [%p] and it couldn't find it in the "
         "TLB so the MMU has to check the PAGE TABLES\n",
         pid, address);
}

void MMU_raise_page_fault(MMU *mmu, void *address, size_t pid) {
  mmu->num_page_faults++;
  printf(
      "Process [%lu] tried to access [%p] and the MMU got an invalid entry\n",
      pid, address);
}

void MMU_free_process_tables(MMU *mmu, size_t pid) {
  PageTable *base_pt = mmu->base_pts[pid];
  Pagetable_delete_tree(base_pt);
}

void MMU_delete(MMU *mmu) {
  for (size_t i = 0; i < MAX_PROCESS_ID; i++) {
    MMU_free_process_tables(mmu, i);
  }
  TLB_delete(mmu->tlb);
  free(mmu);
}
