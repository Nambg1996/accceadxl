void runFunctionEvery(void (*task)(), unsigned long interval_ms)
{

    /* how to use
    void myTask() {

  Serial.println("Ice Ice Baby");
}

runFunctionEvery(&myTask, 5000);


     */

    static unsigned long previousTime = 0;

    unsigned long currentTime = millis();

    if (currentTime - previousTime >= interval_ms)
    {
        task();
        previousTime = currentTime;
    }
}