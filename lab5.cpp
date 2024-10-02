#include <iostream>

int main() {
    long X = 2;            // Змінна для аргументу
    long REZ;             // Змінна для результату

    __asm {               // Початок асемблерної вставки
        lea EBX, REZ     // Завантаження адреси результату в регістр EBX

        // Обчислення знаменника: 5 * x^2 + 8
        mov EAX, X       // EAX = x
        imul EAX, EAX    // EAX = x^2
        imul EAX, 5      // EAX = 5 * x^2
        add EAX, 8       // EAX = 5 * x^2 + 8
        mov EDI, EAX     // Зберігаємо знаменник в EDI

        // Обчислення чисельника: 4 * x^2 - 12
        mov EAX, X       // EAX = x
        imul EAX, EAX    // EAX = x^2
        imul EAX, 4      // EAX = 4 * x^2
        sub EAX, 12      // EAX = 4 * x^2 - 12

        cdq               // Розширення EAX в EDX:EAX для ділення
        idiv EDI         // Ділимо EAX на EDI (EAX / EDI), результат в EAX, залишок в EDX

        // Округлення результату
        cmp EDX, 0       // Перевірка залишку
        jz  no_rounding   // Якщо залишок 0, не потрібно округлювати
        add EAX, 1       // Якщо залишок > 0, округлюємо вгору

        no_rounding:
        mov[EBX], EAX   // Запис результату в пам'ять
    }

    std::cout << "Result: " << REZ << std::endl; // Виводимо результат на екран
    return 0;
}
