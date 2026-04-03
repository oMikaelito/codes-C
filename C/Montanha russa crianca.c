using System;

public class HelloWorld
{
    public static void Main(string[] args)
    {
        int idade;
        Console.Write("Qual e a idade da crianca? \n");
        idade = int.Parse(Console.ReadLine());

        if (idade >= 10){
            Console.WriteLine("\nPermitido a entrada!");
        } else {
            Console.WriteLine("\nEntrada negada!");
        }
    }
}