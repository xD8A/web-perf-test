FROM python:3.9-alpine3.15

RUN apk update \
    && apk add --virtual build-deps --no-cache gcc python3-dev musl-dev \
    && pip install --no-cache-dir asyncpg uvicorn \
    && apk del build-deps

COPY . /app
WORKDIR /app

RUN chown -R nobody: /app
USER nobody

EXPOSE 5000
CMD ["uvicorn", "--host=0.0.0.0", "--port=5000", "main:app"]
