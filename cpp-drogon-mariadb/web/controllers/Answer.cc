/**
 *
 *  Answer.cc
 *  This file is generated by drogon_ctl
 *
 */

#include "Answer.h"
#include <string>


/*
void Answer::getOne(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    std::string &&id)
{
}*/

void Answer::get(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto models = m_mapper.findAll();

    Json::Value respData(Json::arrayValue);
    for (size_t i = 0; i < models.size(); i++)
    {
        auto model = models.at(i);
        respData.append(model.toJson());
    }

    auto resp = HttpResponse::newHttpJsonResponse(respData);
    callback(resp);
}

void Answer::create(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback)
{
    Json::Value reqData = *req->jsonObject();
    assert(reqData.isObject());

    drogon_model::web::Answers model(reqData);
    m_mapper.insert(model);
    // TODO: update id
    
    Json::Value respData = model.toJson();
    auto resp = HttpResponse::newHttpJsonResponse(respData);
    callback(resp);
}

/*
void Answer::updateOne(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&id)
{
}*/

/*
void Answer::update(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback)
{

}*/

/*
void Answer::deleteOne(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&id)
{
}*/
