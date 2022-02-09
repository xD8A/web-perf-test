import json
import asyncpg


async def read_body(receive):
    body = b''
    more_body = True

    while more_body:
        message = await receive()
        body += message.get('body', b'')
        more_body = message.get('more_body', False)

    return body


async def app(scope, receive, send):
    conn = await asyncpg.connect('postgresql://web:password@db/web')
    try:
        if scope.get('method') == 'POST':
            #headers = dict(scope.get('headers', []))
            #n = int(headers.get('content-length', 0))
            data = await read_body(receive)
            answer = json.loads(data.decode('utf-8'))
            answer_id = await conn.fetchval('INSERT INTO answers (question_id, answer) VALUES ($1, $2) RETURNING id', 
                                            int(answer['question_id']), 
                                            str(answer['answer']))
            answer['id'] = int(answer_id)
            data = json.dumps(answer).encode('utf-8')

        else:

            rows = await conn.fetch('SELECT id, question_id, answer FROM answers')
            answers = [dict(zip(('id', 'question_id', 'answer'), r)) for r in rows]
            data = json.dumps(answers).encode('utf-8')
        
    finally:
        conn.close()

    await send({
        'type': 'http.response.start',
        'status': 200,
        'headers': [
            [b'content-type', b'application/json'],
        ],
    })
    await send({
        'type': 'http.response.body',
        'body': data,
    })
