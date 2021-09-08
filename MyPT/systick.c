#include "systick.h"
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
/*---------------------------------------------------------------------------*/
/** \brief  systick init
 *
 * \param
 * \param
 * \return
 *
 */

void SysTickInit(void)
{
    /* SYSTICK configuration */
    WdogInit();
    //
    DI();
    //
    /* SYSTICK configuration */
    //
    EI();
}
/*---------------------------------------------------------------------------*/
/** \brief  watchdog init
 *
 * \param
 * \param
 * \return
 *
 */
void WdogInit(void)
{
}
/*---------------------------------------------------------------------------*/
/** \brief  watchdog reset
 *
 * \param
 * \param
 * \return
 *
 */
void WdogRst(void)
{
}
