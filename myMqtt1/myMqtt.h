
#ifndef myMQTT_H
#define myMQTT_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct keyValuePairTag
    {
      char* key;
      char* value;
    } KeyValuePair;

    bool init_mqtt(const char* connectionString);
    bool do_mqtt();

    void processMessage(int Count, KeyValuePair properties[]);
    void sendString (char* buf);

#ifdef __cplusplus
}
#endif

#endif 
