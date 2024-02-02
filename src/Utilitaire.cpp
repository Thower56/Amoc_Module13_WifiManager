#include <Utilitaire.h>

Timer::Timer(double p_second, THandlerFunction p_function){
    m_function = p_function;
    m_derniereDateChangement = 0;
    m_second = p_second;
}

void Timer::tick(){

    long dateActuelle = millis();
    if(dateActuelle - m_derniereDateChangement > (m_second * 1000)) {
        m_function();
        m_derniereDateChangement = dateActuelle;
    }
};

String readJson(fs::FS &fs, const char * path){

    #if DEBUG
        Serial.println(path);
    #endif

    String json;

    File file = fs.open(path);
    if(!file || file.isDirectory()){

        #if DEBUG
        Serial.println("- failed to open file for reading");
        #endif
        
        return String("error");
    }

    #if DEBUG
        Serial.println("- read from file:");
    #endif

    
    char temp;
    while(file.available()){
        temp = file.read();
        json += static_cast<char>(temp);
    }
    file.close();
    return (String)json;
}

void writeJson(fs::FS &fs, const char * path, const String p_Json){

    #if DEBUG
        Serial.printf("Writing file: %s\r\n", path);
    #endif
    

    File file = fs.open(path, FILE_WRITE);
    if(!file){

        #if DEBUG
            Serial.print("File : ");
            Serial.println(file);
            Serial.println("- failed to open file for writing");
        #endif

        return;
    }
    if(file.print(p_Json)){

        #if DEBUG
            Serial.println("- file written");
        #endif
        
    } else {

        #if DEBUG
            Serial.println("- write failed");
        #endif
        
    }
    file.close();
}
