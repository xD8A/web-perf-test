import json
import MySQLdb


def app(env, start_response):
    conn = MySQLdb.connect(host='db', user='web', password='password', db='web')
    try:
        if env.get('REQUEST_METHOD') == 'POST':
            n = int(env.get('CONTENT_LENGTH', 0))
            data = env['wsgi.input'].read(n)
            answer = json.loads(data.decode('utf-8'))
            with conn.cursor() as cur:
                cur.execute('INSERT INTO answers (question_id, answer) VALUES (%s, %s)', 
                            (answer['question_id'], answer['answer']))
                answer_id = cur.fetchone()
                answer['id'] = int(conn.insert_id())
                conn.commit()
            data = json.dumps(answer).encode('utf-8')
            start_response('200 OK', [('Content-Type', 'text/plain')]) 
            return [data]

        with conn.cursor() as cur:
            cur.execute('SELECT id, question_id, answer FROM answers')
            answers = cur.fetchall()
        answers = [dict(zip(('id', 'question_id', 'answer'), a)) for a in answers]
        data = json.dumps(answers).encode('utf-8')
        start_response('200 OK', [('Content-Type', 'application/json')])
        return [data]
    finally:
        conn.close()
