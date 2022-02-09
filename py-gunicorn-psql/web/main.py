import json
import psycopg2


def app(env, start_response):
    conn = psycopg2.connect(dbname='web', user='web', password='password', host='db')
    try:
        if env.get('REQUEST_METHOD') == 'POST':
            n = int(env.get('CONTENT_LENGTH', 0))
            data = env['wsgi.input'].read(n)
            answer = json.loads(data.decode('utf-8'))
            with conn.cursor() as cur:
                cur.execute('INSERT INTO answers (question_id, answer) VALUES (%s, %s) RETURNING id', 
                            (int(answer['question_id']), str(answer['answer'])))
                answer_id = cur.fetchone()[0]
                conn.commit()
            answer['id'] = int(answer_id)
            data = json.dumps(answer).encode('utf-8')
        else:
            with conn.cursor() as cur:
                cur.execute('SELECT id, question_id, answer FROM answers')
                rows = cur.fetchall()
            answers = [dict(zip(('id', 'question_id', 'answer'), r)) for r in rows]
            data = json.dumps(answers).encode('utf-8')
    finally:
        conn.close()

    start_response('200 OK', [('Content-Type', 'application/json')])
    return [data]

