intsum(inta, intb)
{
 ints = a + b;
 returns;
}
boolsearch(int *arr, intkey)
{
 inti;
 for (i = 0; i < 10; i++)
 {
 if (arr[i] == key)
 returntrue;
 elsereturnfalse;
 }
}
voidmain()
{
 inta[20], i, res;
 boolstatus;
 printf("Enterarrayelements:");
 for (i = 0; i < 10; ++i)
 scanf("%d", &a[i]);
 res = sum(a[0], a[4]);
 status = search(a, res);
 printf("%d", status);
}