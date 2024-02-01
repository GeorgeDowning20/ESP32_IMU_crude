#pragma once

float lpf(float breakf, float samplef, float input, float *buff)
{
    float alpha = 1 / (1 + (2 * 3.14159 * breakf / samplef));
    float output = alpha * input + (1 - alpha) * *buff;
    *buff = output;
    return output;
}

float hpf(float breakf, float samplef, float input, float *buff)
{
    float alpha = 1 / (1 + (2 * 3.14159 * breakf / samplef));
    float output = alpha * *buff + alpha * (input - *buff);
    *buff = output;
    return output;
}

float bpf(float breakf_high, float breakf_low, float samplef, float input, float *buff)
{
    float alpha_high = 1 / (1 + (2 * 3.14159 * breakf_high / samplef));
    float alpha_low = 1 / (1 + (2 * 3.14159 * breakf_low / samplef));

    float output = alpha_high * input + (1 - alpha_high) * *buff;
    output = alpha_low * *buff + alpha_low * (output - *buff);
    *buff = output;
    return output;
}

float threshold(float input, float threshold)
{
    if (input > threshold)
    {
        return input;
    }
    else if (input < -threshold)
    {
        return input;
    }
    else
    {
        return 0;
    }
}