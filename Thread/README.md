# �����߳�
CreateThread �� _beginthreadex �������������̵߳ĺ����������Ƿֱ����ڲ�ͬ�Ŀ�Ͳ�Σ�

    CreateThread
        ��Դ��CreateThread �� Windows API ��һ���֣�ֱ���ڲ���ϵͳ���𴴽��̡߳�
        ���ܣ����ṩ�˴����͹����̵߳Ļ������ܣ����������߳����ȼ����̰߳�ȫ�ԡ��߳������ĵȡ�
        ʹ�ã�ͨ��������Ҫֱ�ӷ��ʵײ�ϵͳ���ܻ��� Windows API ���ܼ��ɵ�Ӧ�ó����С�
        ��Դ������CreateThread �����Զ��������߳�������� CRT ��Դ�������� (errno) �������ֲ߳̾��洢������

    _beginthreadex
        ��Դ��_beginthreadex �� Microsoft C Runtime (CRT) ���һ���֣����Ƕ� CreateThread �ķ�װ���ṩ�˸��߲�ε��̴߳������ܡ�
        ���ܣ������ṩ�������̴߳��������⣬_beginthreadex �������ʼ�������� CRT ������ȷ��ÿ���̶߳������Լ��� CRT ״̬��
        ʹ�ã���ʹ�� C/C++ ���������� Visual C++����д�ĳ����У��Ƽ�ʹ�� _beginthreadex����Ϊ�����������߳���ص� CRT ��Դ��������ֹ�ڴ�й©��
        ��Դ������_beginthreadex �ڲ���Ϊÿ�����̷߳���һ�����ݽṹ��ͨ����Ϊ tiddata�������ڴ洢�߳����е� CRT ���ݡ����߳̽���ʱ��ͨ�� _endthreadex �����Զ�������Щ��Դ��

��Ҫ�����ܽ᣺

    ��������CreateThread ֱ�ӵ��� Windows API���� _beginthreadex �� CRT ��һ���֣����ڲ������� CreateThread��
    ��Դ������_beginthreadex �������߳����е� CRT ��Դ����������������ͷ��߳����ݽṹ���� CreateThread �򲻸�����Щ����
    �ֲ߳̾��洢��_beginthreadex ��֤ÿ���̶߳����Լ��� CRT �����������ֲ߳̾��Ĵ���ź�����ȫ�ֱ����������˶��̼߳�����ݳ�ͻ��
    ���ý��飺��ʹ�� Microsoft Visual C++ ������ʱ������ʹ�� _beginthreadex �� _endthreadex �������ͽ����̣߳���ȷ����ȷ���� CRT ��Դ��

���ִ� C++ ����У����Ƽ�ʹ�� C++11 ��׼���е� <thread>�����ṩ�˸��߼���������ʹ���ҿ�ƽ̨���̹߳����ӿڡ�



