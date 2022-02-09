/**
 *
 *  Answer.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "../models/Answers.h"

using namespace drogon;
/**
 * @brief this class is created by the drogon_ctl command (drogon_ctl create controller -r Answer).
 * this class is a restful API controller.
 */
class Answer: public drogon::HttpController<Answer>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    //METHOD_ADD(Answer::getOne,"/{1}",Get,Options);
    METHOD_ADD(Answer::get,"",Get,Options);
    METHOD_ADD(Answer::create,"",Post,Options);
    //METHOD_ADD(Answer::updateOne,"/{1}",Put,Options);
    //METHOD_ADD(Answer::update,"",Put,Options);
    //METHOD_ADD(Answer::deleteOne,"/{1}",Delete,Options);
    METHOD_LIST_END

//    void getOne(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback,
//                std::string &&id);
//    void updateOne(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback,
//                std::string &&id);
//    void deleteOne(const HttpRequestPtr &req,
//                   std::function<void(const HttpResponsePtr &)> &&callback,
//                   std::string &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);

//    void update(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback);

private:
    drogon::orm::Mapper<drogon_model::web::Answers> m_mapper = drogon::orm::Mapper<drogon_model::web::Answers>(app().getDbClient());

};
