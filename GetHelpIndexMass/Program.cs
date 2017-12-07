using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MyUtilites;

/*
	а) Написать программу, которая запрашивает массу и рост человека, 
    вычисляет его индекс массы и сообщает, нужно ли человеку похудеть, 
    набрать вес или все в норме;
    б) * Рассчитать, на сколько кг похудеть или сколько кг набрать для нормализации веса.

    Разработчик:
    Корепанов С.Е.
*/
namespace GetHelpIndexMass
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите вес человека, кг.: ");
            float weight = Convert.ToSingle(Console.ReadLine());
            Console.Write("Введите рост человека, м: ");
            float height = Convert.ToSingle(Console.ReadLine());

            float BodyMassIndex = getIndexMass(weight, height);
            Console.WriteLine("Индекс массы тела равен {0:F}", BodyMassIndex);

            float minNormWeight = 18.5f;
            float maxNormWeight = 24.99f;

            if (BodyMassIndex < minNormWeight)
            {
                Console.WriteLine("Вам рекомендуется прибавить вес на {0} кг.", (getWeight(minNormWeight, height) - weight) );
            } 
            else
            {
                if (BodyMassIndex > 24.99)
                {
                    Console.WriteLine("Вам рекомендуется сбросить вес на {0} кг.", (weight-getWeight(maxNormWeight, height)) );
                }
                else Console.WriteLine("Ваш вес в норме");
            }

            MyConsole.Pause();
        }

        static float getIndexMass(float weight, float height)
        {
             return weight / (height * height);
        }

        static float getWeight(float IndexMass, float height)
        {
            return IndexMass * (height * height);
        }

    }
}
