FROM python:3.9-alpine3.15

RUN apk update \
    && apk add --no-cache libpq libev-dev \
    && apk add --virtual build-deps --no-cache gcc python3-dev musl-dev postgresql-dev \
    && pip install --no-cache-dir psycopg2 bjoern \
    && apk del build-deps

COPY . /app
WORKDIR /app

RUN chown -R nobody: /app
USER nobody

EXPOSE 5000
CMD ["python3", "-u", "run.py"]
