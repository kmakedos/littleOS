/*
 * =====================================================================================
 *
 *       Filename:  test3.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  13/10/2020 12:48:25 πμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

void caller_function(){
    callee_function(0xdede);
}

int callee_function(int myarg){
    return myarg;
}
