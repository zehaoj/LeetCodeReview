//
// Created by zehao on 2020-08-20.
//

#include "VADProcessing.h"
#include "definitions.h"
#include "utils.h"
#include <signal.h>
#include "CallBackPointers.h"
#include "VoiceActivityDetector.h"


SpeakerStreamReader::VADProcessing(VoiceActivityDetector *voiceActivityDetector) : vad(voiceActivityDetector) {}

void VADProcessing::start() {
    doRun = true;
    readingThread = std::thread(&VADProcessing::run, this);
}

void VADProcessing::stop() {
    doRun = false;
    if (readingThread.joinable()) {
        readingThread.join();
    } else {
        std::wcerr << "Could not join readingThread" << std::endl;
    }
}

void VADProcessing::run() {
    utils::printDebugMessage("VADProcessing", "Started VAD thread");
    try {
        while (doRun) {
            vad->process(&audio16Khz, &speaker, cbPointers->blob,
                                                    cbPointers->request, cbPointers->output, 0.5);
            //if the samplerate is not 16000, downsample the audioData
            //if the # channels >1 , downchannel.
            //write data to buffer
        }
    } catch (zmq::error_t &e) {
        utils::printDebugMessage("VADProcessing", "Unexpected death");
        utils::printDebugMessage("VADProcessing", e.what());
    }

    utils::printDebugMessage("VADProcessing", "Ending VAD thread");
}
