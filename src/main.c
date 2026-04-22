#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <pwm_z42.h>  
/* * 1. Referenciamos o nó 'gpioe' diretamente pelo nome do objeto no DTS.
 * O Zephyr encontrará o endereço 0x400ff100 automaticamente.
 */
#define GPIOE_NODE DT_NODELABEL(gpioe)
#define TPM_MODULE 1000
// O pino que você deseja (PTE20)
#define INPUT_PIN1 20 
#define INPUT_PIN2 21
int main(void)
{
    /* * 2. DEVICE_DT_GET obtém o dispositivo sem precisar de strings (labels).
     * Isso resolve o erro "Erro ao acessar porta".
     */
    const struct device *input_dev = DEVICE_DT_GET(GPIOE_NODE);
    int ret1, ret2, val1, val2;
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
     pwm_tpm_Ch_Init(TPM0, 2, TPM_PWM_H, GPIOE, 29);
     pwm_tpm_Ch_Init(TPM0, 3, TPM_PWM_H, GPIOE, 30);
     pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOC, 1);
     pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOC, 2);
    ret1 = gpio_pin_configure(input_dev, INPUT_PIN1, GPIO_INPUT | GPIO_PULL_UP);
    if (ret1 != 0) {
        printk("Erro ao configurar pino %d\n", INPUT_PIN1);
        return 0;
    }

     ret2 = gpio_pin_configure(input_dev, INPUT_PIN2, GPIO_INPUT | GPIO_PULL_UP);
    if (ret2 != 0) {
        printk("Erro ao configurar pino %d\n", INPUT_PIN2);
        return 0;
    }
    


    while (1) {


        val1 = gpio_pin_get(input_dev, INPUT_PIN1);
        val2 = gpio_pin_get(input_dev, INPUT_PIN2);
        printk("%d", val1);
        printk("%d", val2);

        if (val1 == 0 && val2 == 1) {
        pwm_tpm_CnV(TPM0, 0, 725);
        pwm_tpm_CnV(TPM0, 1, 0);
        pwm_tpm_CnV(TPM0, 2, 0);
        pwm_tpm_CnV(TPM0, 3, 450);
        }
        else if (val1 == 1 && val2 == 0) {
        pwm_tpm_CnV(TPM0, 0, 0);
        pwm_tpm_CnV(TPM0, 1, 450);
        pwm_tpm_CnV(TPM0, 2, 725);
        pwm_tpm_CnV(TPM0, 3, 0);
        }
        else if (val1 == 1 && val2 == 1) {
        pwm_tpm_CnV(TPM0, 0, 500);
        pwm_tpm_CnV(TPM0, 1, 0);
        pwm_tpm_CnV(TPM0, 2, 500);
        pwm_tpm_CnV(TPM0, 3, 0);
        }
        else if (val1 == 0 && val2 == 0) {
        pwm_tpm_CnV(TPM0, 0, 900);
        pwm_tpm_CnV(TPM0, 1, 0);
        pwm_tpm_CnV(TPM0, 2, 900);
        pwm_tpm_CnV(TPM0, 3, 0);
        }
        k_msleep(10);
        
    }

}