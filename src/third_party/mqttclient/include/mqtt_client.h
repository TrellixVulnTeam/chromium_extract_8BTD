/*********************************************
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
           ���汣��       ����BUG
           �����޷�       ��������
           ��������       �����Ը
*********************************************/

/**
 * @brief mqttclient
 * @date 2017-01-10
 * @author neeker
 */

#ifndef __mqtt_client_h__
#define __mqtt_client_h__

#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include <string>
#include <vector>

namespace net {

//MQTT�ͻ���
class MQTTClient : public base::RefCounted<MQTTClient> {
public:

  //QoS����
  enum QoSLevel {
    Qos0,
    Qos1,
    Qos2
  };

  //MQTT�汾����
  enum MQTTVersion {
    MQTTV31 = 3,
    MQTTV311 = 4,
  };

  class Params {
  public:

    Params() :
      mqtt_version(MQTTVersion::MQTTV311),
      reconnect_delay_seconds(30),
      keep_alive_interval(30),
      clear_session(true),
      publish_retry_max(3) {
    }

    Params(const Params& o) {
      *this = o;
    }

    Params& operator=(const Params& o) {
      mqtt_version = o.mqtt_version;
      reconnect_delay_seconds = o.reconnect_delay_seconds;
      keep_alive_interval = o.keep_alive_interval;
      client_id = o.client_id;
      username = o.username;
      password = o.password;
      clear_session = o.clear_session;
      publish_retry_max = o.publish_retry_max;
      return *this;
    }

    //����MQTT�汾
    MQTTVersion mqtt_version;

    //���������ӳ�����
    size_t reconnect_delay_seconds;

    //����KeepAlive���
    size_t keep_alive_interval;

    //���ÿͻ���ID
    std::string client_id;

    //�����û���
    std::string username;

    //�����û�����
    std::string password;

    //�����˳��Ƿ�����Ự
    bool clear_session;

    //���÷���������Դ���
    size_t publish_retry_max;

  };

  virtual ~MQTTClient() {}

  //����
  virtual bool Startup() = 0;

  //ֹͣ
  virtual void Shutdown() = 0;

  //�ȴ�ֹͣ
  virtual void WaitShutdown() = 0;

  //�Ƿ���������
  virtual bool IsRunning() const = 0;

  //�ȴ�ֹͣ(��ʱ����false)
  virtual bool TimeWaitShutdown(const base::TimeDelta &max_time) = 0;

  //��������
  virtual void SubscribeTopic(const std::string &topic_name, int qos = 0) = 0;

  //ȡ����������
  virtual void UnSubscribeTopic(const std::string &topic_name) = 0;

  //��������, pidΪ��ϢΨһ���
  virtual void PublishMessage(const std::string &topic_name,
    const std::string &pid, const std::vector<char> &data,
    int qos = 0, bool retain = false) = 0;

  //������Ϣ����
  enum PublishError {

    //�ﵽ������Դ���
    ERROR_PUBISH_MAXRETRY = 8,

    //�ѱ�ȡ��(�ͻ��˱�ֹͣʱ)
    ERROR_PUBLISH_CANCEL = 9,

  };

  //�ͻ���״̬
  enum ClientState {

    //������
    MQTT_ClientStartup,

    //������
    MQTT_RemoteConnecting,

    //�޷�����
    MQTT_RemoteConnectError,

    //������
    MQTT_RemoteConnected,

    //�ѶϿ�
    MQTT_RemoteDisConnected,

    //��ֹͣ
    MQTT_ClientShutdown,

  };

  class Observer {
  public:

    //������
    virtual void OnStateChanged(int state) = 0;

    //�Ѷ���������
    virtual void OnTopicSubscribed(const std::string &topic_name, int qos) = 0;

    //�ѽⶩ������
    virtual void OnTopicUnSubscribed(const std::string &topic_name) = 0;

    //��������յ���Ϣ(QoS=2)ʱ, handled=true��ʾ����
    virtual void OnPublishMessageServerReceived(const std::string &topic_name, const std::string &pid, bool *handled) = 0;

    //��Ϣ�ѷ���, PID��ʾ�������Ϣpid
    virtual void OnPublishMessageFinalFinished(const std::string &topic_name, const std::string &pid) = 0;

    //��Ϣ�������*handle=true��ʾ�Ѵ���, qos=2ʱ����Ҫ��OnMessageArrivaledServerReply����msgid����Ϣ
    virtual void OnRemoteMessageArrivaled(const std::string &topic_name, uint8_t *data, size_t datasiz,
      int msgid, int qos, bool *handled) = 0;

    //��Ϣ���������Ӧ�𷵻�(QoS=2)�Ż�
    virtual void OnRemoteMessageServerReply(int msgid, bool *handled) = 0;

    //��Ϣ��������(����������֮���ֹͣ����δ�����)
    virtual void OnPublishMessageOccurError(int err,
      const std::string &topic_name,
      const std::string &pid, const std::vector<char> &data,
      int qos, bool retain) = 0;

    virtual void OnIdle() = 0;

  };

  virtual void SetObserver(Observer *val) = 0;

};

}

#endif /** __mqtt_client_h__ */

