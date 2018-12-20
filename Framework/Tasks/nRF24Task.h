/*
 *
 *
 *  Created on: 06.07.2018
 *      Author: harald
 */

#ifndef StartnRF24Tsk_H_
#define StartnRF24Tsk_H_

/**
 * Used as link between C-call from main to Start...Task().
 * Does not need to be instantiated, if no use of C++ calls to other
 * classes is done.
 */



// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif



EXTERNC void StartnRF24Tsk(void const * argument);
//EXTERNC int lw_main(void);

#undef EXTERNC
#ifdef __cplusplus

// put cpp includes here!!



#endif // C interface
#endif /* StartnRF24Tsk_H_ */
