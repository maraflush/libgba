/*
	"$Id: gba_interrupt.h,v 1.6 2005-10-05 12:08:49 wntrmute Exp $"

	Header file for libgba interrupt handling

	Copyright 2003-2004 by Dave Murphy.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA.

	Please report all bugs and problems through the bug tracker at
	"http://sourceforge.net/tracker/?group_id=114505&atid=668551".

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_interrupt.h,v 1.6 2005-10-05 12:08:49 wntrmute Exp $"

*/

/*! \file gba_interrupt.h
    \brief gba interrupt support.

*/

#ifndef _gba_interrupt_h_
#define _gba_interrupt_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

/*! \var typedef void ( * IntFn)(void)
    \brief A type definition for an interrupt function pointer
*/
typedef void ( * IntFn)(void);

struct IntTable{IntFn handler; u32 mask;};

#define MAX_INTS	15

#define INT_VECTOR	*(IntFn *)(0x03007ffc)		// BIOS Interrupt vector
/*! \def REG_IME

    \brief Interrupt Master Enable Register.

	When bit 0 is clear, all interrupts are masked.  When it is 1,
	interrupts will occur if not masked out in REG_IE.

*/
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
/*! \def REG_IE

    \brief Interrupt Enable Register.

	This is the activation mask for the internal interrupts.  Unless
	the corresponding bit is set, the IRQ will be masked out.
*/
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
/*! \def REG_IF

    \brief Interrupt Flag Register.

	Since there is only one hardware interrupt vector, the IF register
	contains flags to indicate when a particular of interrupt has occured.
	To acknowledge processing interrupts, set IF to the value of the
	interrupt handled.

*/
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request

//!  interrupt masks.
/*!
  These masks are used in conjuction with REG_IE to enable specific interrupts
  and with REG_IF to acknowledge interrupts have been serviced.
*/
typedef enum irqMASKS {
	IE_VBL		=	(1<<0),		/*!< vertical blank interrupt mask */
	IE_HBL		=	(1<<1),		/*!< horizontal blank interrupt mask */
	IE_VCNT		=	(1<<2),		/*!< vcount match interrupt mask */
	IE_TIMER0	=	(1<<3),		/*!< timer 0 interrupt mask */
	IE_TIMER1	=	(1<<4),		/*!< timer 1 interrupt mask */
	IE_TIMER2	=	(1<<5),		/*!< timer 2 interrupt mask */
	IE_TIMER3	=	(1<<6),		/*!< timer 3 interrupt mask */
	IE_SERIAL	=	(1<<7),		/*!< serial interrupt mask */
	IE_DMA0		=	(1<<8),		/*!< DMA 0 interrupt mask */
	IE_DMA1		=	(1<<9),		/*!< DMA 1 interrupt mask */
	IE_DMA2		=	(1<<10),	/*!< DMA 2 interrupt mask */
	IE_DMA3		=	(1<<11),	/*!< DMA 3 interrupt mask */
	IE_KEYPAD	=	(1<<12),	/*!< Keypad interrupt mask */
	IE_GAMEPAK	=	(1<<13)		/*!< horizontal blank interrupt mask */
} irqMASK;

extern struct IntTable IntrTable[];

/*! \fn void InitInterrupt(void)
    \brief initialises the gba interrupt code.

*/
void InitInterrupt(void);

/*! \fn IntFn *SetInterrupt(irqMASK mask, IntFn function)
    \brief sets the interrupt handler for a particular interrupt.

	\param mask
	\param function
*/
IntFn *SetInterrupt(irqMASK mask, IntFn function);

/*! \fn void EnableInterrupt(irqMASK mask)
    \brief allows an interrupt to occur.

	\param mask
*/
void EnableInterrupt(irqMASK mask);

/*! \fn void DisableInterrupt(irqMASK mask)
    \brief prevents an interrupt occuring.

	\param mask
*/
void DisableInterrupt(irqMASK mask);

void IntrMain();



//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_interrupt_h_
